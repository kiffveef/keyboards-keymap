#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(

		KC_ESC,  KC_Q,    KC_P,    KC_LBRC, KC_RBRC,
		MT(MOD_LCTL,KC_TAB),KC_A,    KC_SCLN, KC_QUOT, KC_BSLS,
		KC_LSFT, KC_Z,    KC_DOT,  KC_SLSH, KC_RSFT,
		KC_LALT, KC_RALT,
		KC_W,    KC_E,    KC_R,    KC_T,
		KC_S,    KC_D,    KC_F,    KC_G,
		KC_X,    KC_C,    KC_V,    KC_B,
		KC_LGUI, LT(1, KC_DEL),LT(1, KC_SPC),
		KC_Y,    KC_U,    KC_I,    KC_O,
		KC_H,    KC_J,    KC_K,    KC_L,
		KC_N,    KC_M,    KC_COMM,
		 LT(1, KC_ENT),  LT(1, KC_BSPC),KC_RGUI
	),

	[1] = LAYOUT(

		KC_GRV,  KC_NO,   KC_NO,   KC_MINS, KC_EQL,
		KC_NO,   KC_1,    KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_6,    KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_NO,
		KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_2,    KC_3,    KC_4,    KC_5,
		KC_7,    KC_8,    KC_9,    KC_0,
		KC_NO,   KC_LSFT, MO(2),
		KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
		KC_NO,   KC_NO,   KC_NO,
		MO(2),   KC_LSFT, KC_NO
	),

	[2] = LAYOUT(

		KC_NO,   KC_F1,   KC_F10,  KC_F11,  KC_F12,
		RGB_TOG, RGB_VAI, KC_NO,   KC_NO,   KC_NO,
		KC_NO,   RGB_VAD, KC_NO,   KC_NO,   KC_NO,
		EE_CLR,  QK_BOOT,
		KC_F2,   KC_F3,   KC_F4,   KC_F5,
		RGB_SAI, RGB_HUI, RGB_SPI, KC_NO,
		RGB_SAD, RGB_HUD, RGB_SPD, KC_NO,
		KC_NO,   KC_NO,   KC_NO,
		KC_F6,   KC_F7,   KC_F8,   KC_F9,
		KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_NO,   KC_NO
	),

	[3] = LAYOUT(

		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS
	),

	[4] = LAYOUT(

		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS
	),

	[5] = LAYOUT(

		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS
	),

	[6] = LAYOUT(

		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS
	),

	[7] = LAYOUT(

		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS
	),

};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
	int current_layer = get_highest_layer(layer_state | default_layer_state);
	// デフォルトレイヤーではインジケーター非表示
	if (current_layer == 0) return false;

	HSV hsv = {0, 255, rgb_matrix_get_val()};
	if (current_layer == 1) {
		hsv.h = 213; //MAGENTA
	} else if (current_layer == 2) {
		hsv.h = 85;  //GREEN
	} else if (current_layer == 3) {
		hsv.h = 43;  //YELLOW
	} else if (current_layer == 4) {
		hsv.h = 21;  //ORANGE
	} else if (current_layer == 5) {
		hsv.h = 192; //PURPLE
	} else if (current_layer == 6) {
		hsv.h = 170; //BLUE
	} else if (current_layer == 7) {
		hsv.h = 0;   //RED
	}
	RGB rgb = hsv_to_rgb(hsv);

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
