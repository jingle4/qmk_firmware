#include QMK_KEYBOARD_H

enum alt_keycodes {
	MD_BOOT //Restart into bootloader after hold timeout
};

enum alt_layers {
	DEF = 0,
	FUNC
};

// Zeal60-specific keys:
//  EF_INC, EF_DEC,   // next/previous backlight effect
//  H1_INC, H1_DEC,   // Color 1 hue increase/decrease
//  S1_INC, S1_DEC,   // Color 1 saturation increase/decrease
//  H2_INC, H2_DEC,   // Color 2 hue increase/decrease
//  S2_INC, S2_DEC,   // Color 2 saturation increase/decrease
//  BR_INC, BR_DEC,   // backlight brightness increase/decrease

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Default layer
[DEF] = LAYOUT_60_ansi(
	KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
	KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
	KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
	KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
	KC_LGUI, MO(FUNC), KC_LALT,                           KC_SPC,                             KC_RALT, KC_LCTL, KC_RGUI, KC_RCTL),

// Fn1 Layer
[FUNC] = LAYOUT_60_ansi(
	KC_GRV,  KC_F1,   KC_F2,   KC_F3,  KC_F4,  KC_F5,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
	LCG_SWP, H1_INC,  BR_INC,  H1_DEC, S1_INC, S2_INC, KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, _______, _______, _______, _______,
	LCG_NRM, H2_INC,  BR_DEC,  H2_DEC, S1_DEC, S2_DEC, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______,
	KC_TRNS, EF_INC,  EF_DEC,  KC_TRNS, _______, _______,  KC_END,  _______, _______, _______, _______, _______,
	KC_TRNS, KC_TRNS,  KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;
    
    switch (keycode) {
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                     reset_keyboard();
                }
            }
            return false;
	default:
	    return true; // Process all other keycodes normally
    }
}
