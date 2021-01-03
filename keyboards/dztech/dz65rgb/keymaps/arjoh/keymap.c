#include QMK_KEYBOARD_H

/* TapDance */
enum {
    TD_GRV_ESC
};

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Grave, twice for Esc Lock
    [TD_GRV_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_ESC),
};

/* "Active" colors */
const uint8_t ACTIVE_COLOR[3] = {0x80, 0x00, 0x80};
const uint8_t DEFAULT_COLOR[3] = {0x00, 0x84, 0xFF};
const uint8_t GAME_COLOR[3] = {0xFF, 0x00, 0x00};

/* layers, ordering is important */
enum layers {
    _MAIN,
    _MACOS,
    _CONTROL,
    _WASD,
    _DESTINY2
}

/* Which LEDs should be active for which layer?
*/
const layers_leds_map[] = {
    [_MAIN] = 59,  /* Location of the GUI key in the _MAIN layer */
    [_MACOS] = 60, /* Location of the GUI key in the _MACOS layer */
    [_CONTROL] = 63, /* Location of the key that enables the _CONTROL layer */
    [_WASD] = 14, /* Location of the key that enables the _WASD layer */
    [_DESTINY2] = 29
};

/* The actual keymaps */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = LAYOUT_65_ansi(
        TD(TD_GRV_ESC), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        LT(2,KC_CAPS),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
        KC_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL,        KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, MO(2),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_MACOS] = LAYOUT_65_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______         , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_LALT, KC_LGUI,                            _______                  , _______, _______, _______, _______, _______, _______
    ),
    [_CONTROL] = LAYOUT_65_ansi(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  TG(3),
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, KC_PSCR, KC_SLCK, KC_PAUS, RESET,   TG(4),
        _______, RGB_SPI, RGB_SPD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          EEP_RST, KC_PGDN,
        KC_LSFT         , _______, _______, _______, _______, _______, NK_TOGG, TG(1)  , _______, _______, _______, _______, KC_VOLU, KC_MUTE,
        _______, _______, _______,                            _______,                   _______, _______, KC_MPLY, KC_MPRV, KC_VOLD, KC_MNXT
    ),
    [_WASD] = LAYOUT_65_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______         , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_LGUI, KC_LALT,                            _______                  , _______, _______, _______, _______, _______, _______
    ),
    [_DESTINY2] = LAYOUT_65_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______         , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_LGUI, KC_LALT,                            _______                  , _______, _______, _______, _______, _______, _______
    ),
};

void rgb_matrix_indicators_user(void) {

    if (!g_suspend_state) {
        switch(biton32(layer_state)) {
            case _WASD:
                rgb_matrix_set_color_all(0x00, 0x00, 0x00);

                // W A S D
                rgb_matrix_set_color(17, GAME_COLOR[0], GAME_COLOR[1], GAME_COLOR[2]);
                rgb_matrix_set_color(31, GAME_COLOR[0], GAME_COLOR[1], GAME_COLOR[2]);
                rgb_matrix_set_color(32, GAME_COLOR[0], GAME_COLOR[1], GAME_COLOR[2]);
                rgb_matrix_set_color(33, GAME_COLOR[0], GAME_COLOR[1], GAME_COLOR[2]);

                break;

            case _DESTINY2:

                rgb_matrix_set_color_all(0x00, 0x00, 0x00);

                // W A S D
                rgb_matrix_set_color(17, GAME_COLOR[0], GAME_COLOR[1], GAME_COLOR[2]);
                rgb_matrix_set_color(31, GAME_COLOR[0], GAME_COLOR[1], GAME_COLOR[2]);
                rgb_matrix_set_color(32, GAME_COLOR[0], GAME_COLOR[1], GAME_COLOR[2]);
                rgb_matrix_set_color(33, GAME_COLOR[0], GAME_COLOR[1], GAME_COLOR[2]);

                // UP LEFT DOWN RIGHT
                rgb_matrix_set_color(56, GAME_COLOR[0], GAME_COLOR[1], GAME_COLOR[2]);
                rgb_matrix_set_color(65, GAME_COLOR[0], GAME_COLOR[1], GAME_COLOR[2]);
                rgb_matrix_set_color(66, GAME_COLOR[0], GAME_COLOR[1], GAME_COLOR[2]);
                rgb_matrix_set_color(67, GAME_COLOR[0], GAME_COLOR[1], GAME_COLOR[2]);

                break;
        }
    }

    /* Set CAPS led */
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(30, ACTIVE_COLOR[0], ACTIVE_COLOR[1], ACTIVE_COLOR[2]);
    }

    /* Show "Active" layer. */
    rgb_matrix_set_color(layers_leds_map[biton32(layer_state)], ACTIVE_COLOR[0], ACTIVE_COLOR[1], ACTIVE_COLOR[2]);

}


