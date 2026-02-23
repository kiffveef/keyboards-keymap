#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

enum custom_keycodes {
    MY_GRV = SAFE_RANGE,
    MY_MINS,
    MY_QUOT,
    MY_SCLN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(

		KC_ESC,  KC_Q,    KC_P,    MY_MINS, LT(3,KC_CAPS),
		MT(MOD_LCTL,KC_TAB),KC_A,    MY_SCLN, MY_QUOT, KC_INT3,
		KC_LSFT, KC_Z,    KC_DOT,  KC_SLSH, KC_ENT,
		KC_LGUI, KC_RSFT,
		KC_W,    KC_E,    KC_R,    KC_T,
		KC_S,    KC_D,    KC_F,    KC_G,
		KC_X,    KC_C,    KC_V,    KC_B,
		KC_LALT, LT(2,KC_SPC), LT(1,KC_DEL),
		KC_Y,    KC_U,    KC_I,    KC_O,
		KC_H,    KC_J,    KC_K,    KC_L,
		KC_N,    KC_M,    KC_COMM,
		JP_ZKHK, LT(1,KC_SPC), KC_RALT
	),

	[1] = LAYOUT(

		MY_GRV,  KC_1,    S(KC_8), S(KC_9), S(KC_2),
		KC_NO,   KC_6,    KC_RBRC, KC_BSLS, S(KC_7),
		KC_NO,   KC_NO,   S(KC_RBRC),S(KC_BSLS),KC_NO,
		KC_NO,   KC_NO,
		KC_2,    KC_3,    KC_4,    KC_5,
		KC_7,    KC_8,    KC_9,    KC_0,
		KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_NO,   LT(2,KC_DEL),
		S(KC_1), JP_AT,   S(KC_3), S(KC_4),
		S(KC_5), JP_CIRC,  S(KC_6), S(JP_COLN),
		KC_MINS, S(KC_MINS),JP_UNDS,
		KC_BSPC, KC_NO,   KC_NO
	),

	[2] = LAYOUT(

		KC_NO,   KC_F1,   KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_F6,   KC_INS,  KC_PSCR, KC_NO,
		KC_NO,   KC_F11,  KC_NO,   KC_NO,   KC_NO,
		KC_NO,   MO(3),
		KC_F2,   KC_F3,   KC_F4,   KC_F5,
		KC_F7,   KC_F8,   KC_F9,   KC_F10,
		KC_F12,  KC_NO,   KC_NO,   KC_NO,
		KC_LALT, KC_NO,   KC_DEL,
		KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
		KC_NO,   KC_NO,   KC_NO,
		KC_BSPC, KC_NO,   MO(3)
	),

	[3] = LAYOUT(

		EE_CLR,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_HOME, KC_PGDN, KC_PGUP, KC_END,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS
	),

};

// JIS認識Windows環境でshift状態を保存・復元しながらキーを送信する
// 呼び出し時のshift有無に応じてnormal/shiftedを使い分ける
static inline void tap_jis_key(uint16_t normal, uint16_t shifted) {
    uint8_t saved = get_mods();
    if (saved & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(shifted);
        set_mods(saved);
    } else {
        tap_code16(normal);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MY_GRV:
            if (record->event.pressed) {
                // JIS: S(KC_LBRC)=`  S(KC_EQL)=~
                tap_jis_key(S(KC_LBRC), S(KC_EQL));
            }
            return false;
        case MY_QUOT:
            if (record->event.pressed) {
                // JIS: S(KC_7)='  S(KC_2)="
                tap_jis_key(S(KC_7), S(KC_2));
            }
            return false;
        case MY_MINS:
            if (record->event.pressed) {
                // JIS: KC_MINS=-  JP_UNDS=_
                tap_jis_key(KC_MINS, JP_UNDS);
            }
            return false;
        case MY_SCLN:
            if (record->event.pressed) {
                // JIS: KC_SCLN=;  JP_COLN=:
                tap_jis_key(KC_SCLN, JP_COLN);
            }
            return false;
        case LT(3, KC_CAPS):
            if (record->tap.count && record->event.pressed) {
                // JIS: S(KC_MINS)==  S(KC_SCLN)=+
                tap_jis_key(S(KC_MINS), S(KC_SCLN));
                return false;
            }
            return true;
    }
    return true;
}
