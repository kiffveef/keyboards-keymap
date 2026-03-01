#include QMK_KEYBOARD_H

enum custom_keycodes {
	IME_TOG = QK_USER_0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(

		KC_ESC,  KC_Q,    KC_P,    KC_MINS, LT(3, KC_EQL),
		LCTL_T(KC_TAB), KC_A, KC_SCLN, KC_QUOT, KC_BSLS,
		KC_LSFT, KC_Z,    KC_DOT,  KC_SLSH, KC_ENT,
		KC_LGUI, KC_RSFT,
		KC_W,    KC_E,    KC_R,    KC_T,
		KC_S,    KC_D,    KC_F,    KC_G,
		KC_X,    KC_C,    KC_V,    KC_B,
		KC_LALT, LT(2, KC_SPC), LT(1, KC_DEL),
		KC_Y,    KC_U,    KC_I,    KC_O,
		KC_H,    KC_J,    KC_K,    KC_L,
		KC_N,    KC_M,    KC_COMM,
		IME_TOG, LT(1, KC_SPC), KC_RCTL
	),

	[1] = LAYOUT(

		KC_GRV,  KC_1,    S(KC_9),    S(KC_0),    S(KC_QUOT),
		KC_TRNS, KC_6,    KC_LBRC,    KC_RBRC,    KC_QUOT,
		KC_TRNS, KC_NO,   S(KC_LBRC), S(KC_RBRC), KC_NO,
		TO(0),   KC_RSFT,
		KC_2,    KC_3,    KC_4,    KC_5,
		KC_7,    KC_8,    KC_9,    KC_0,
		KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_NO,   KC_DEL,
		S(KC_1), S(KC_2), S(KC_3), S(KC_4),
		S(KC_5), S(KC_6), S(KC_7), S(KC_8),
		KC_NO,   KC_NO,   KC_NO,
		KC_BSPC, KC_NO,   KC_NO
	),

	[2] = LAYOUT(

		KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,
		TO(0),   TO(0),
		KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_NO,   KC_DEL,
		KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
		KC_NO,   KC_NO,   KC_NO,
		KC_BSPC, KC_NO,   KC_NO
	),

	[3] = LAYOUT(

		LALT(KC_F4), KC_NO, KC_INS,  KC_PSCR, KC_NO,
		KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,
		TO(0),   TO(0),
		KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_NO,   KC_DEL,
		KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_HOME, KC_PGDN, KC_PGUP, KC_END,
		KC_NO,   KC_NO,   KC_NO,
		KC_BSPC, KC_NO,   KC_NO
	),

	[4] = LAYOUT(

		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO,
		TO(0), TO(0),
		KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO
	),

	[5] = LAYOUT(

		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		TO(0), TO(0),
		KC_NO, KC_NO, KC_NO, EE_CLR,
		KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO,
		QK_BOOT, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO
	),


};

// layer_moveによる固定中にLTリリースで解除されるのを防ぐ
// 0=ロックなし、1-5=ロック先レイヤー番号
static uint8_t locked_layer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	// TO(0)によるLayer 0復帰時もロック解除
	if (record->event.pressed && keycode == TO(0)) {
		locked_layer = 0;
	}

	// RShift[3,11] + 数字キーでレイヤー直接移動
	if (record->event.pressed && (get_mods() & MOD_BIT(KC_RSFT))) {
		uint8_t layer = UINT8_MAX;
		switch (keycode) {
		case KC_0: layer = 0; break;
		case KC_1: layer = 1; break;
		case KC_2: layer = 2; break;
		case KC_3: layer = 3; break;
		case KC_4: layer = 4; break;
		case KC_5: layer = 5; break;
		}
		if (layer != UINT8_MAX) {
			unregister_mods(MOD_BIT(KC_RSFT));
			locked_layer = layer;
			layer_move(layer);
			return false;
		}
	}

	switch (keycode) {
	case IME_TOG:
		if (record->event.pressed) {
			tap_code16(LALT(KC_GRV));
		}
		return false;
	}
	return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
	// layer_move固定中はLTリリースによるLayer 0復帰を阻止
	if (locked_layer > 0 && get_highest_layer(state) == 0) {
		return (layer_state_t)1 << locked_layer;
	}
	return state;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
	int current_layer = get_highest_layer(layer_state | default_layer_state);
	// デフォルトレイヤーではインジケーター非表示
	if (current_layer == 0) return false;

	// レイヤー別インジケーターカラー(RGB)
	const uint8_t layer_colors[][3] = {
		{0, 0, 0},
		{222, 194, 59},
		{69, 125, 36},
		{228, 147, 10},
		{193, 57, 94},
		{197, 50, 17},
	};
	if (current_layer >= sizeof(layer_colors) / sizeof(layer_colors[0])) return false;
	uint8_t val = rgb_matrix_get_val();
	RGB rgb = {
		.r = layer_colors[current_layer][0] * val / 255,
		.g = layer_colors[current_layer][1] * val / 255,
		.b = layer_colors[current_layer][2] * val / 255,
	};

	// T/Y(row0), G/H(row1), B/N(row2) - 見下ろした時に中央に並ぶキー
	const uint8_t indicator_leds[] = {5, 6, 18, 19, 31, 32};
	for (uint8_t i = 0; i < 6; i++) {
		uint8_t led = indicator_leds[i];
		if (led >= led_min && led < led_max) {
			rgb_matrix_set_color(led, rgb.r, rgb.g, rgb.b);
		}
	}
	return false;
}
