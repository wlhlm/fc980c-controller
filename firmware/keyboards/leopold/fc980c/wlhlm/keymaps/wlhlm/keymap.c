// Copyright 2024 Wilhelm Schuster
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdio.h>

#include "debug.h"

#include QMK_KEYBOARD_H

extern keyboard_config_t fc980c_config;

enum layer_names {
    KM_BASE_LAYER,
    KM_FUNCTION_LAYER
};

enum custom_keycodes {
    AP_UP = SAFE_RANGE, // make actuation point deeper
    AP_DN,              // make actuation point shallower
    AP_RST,             // reset actuation point to factory value
    AP_PRINT_VAL        // type out current actuation point value (max 63)
};

#define FN MO(KM_FUNCTION_LAYER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [KM_BASE_LAYER] = LAYOUT(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,               KC_DEL,  KC_INS,  KC_PGUP, KC_PGDN,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,              KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,              KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,               KC_P4,   KC_P5,   KC_P6,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,   KC_UP,     KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_CAPS, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RCTL, FN,        KC_LEFT, KC_DOWN, KC_RGHT,   KC_P0,   KC_PDOT
    ),

    [KM_FUNCTION_LAYER] = LAYOUT(
        QK_BOOT,          AP_PRINT_VAL, AP_DN,   AP_UP,   AP_RST,  _______, _______, _______, _______, _______, _______, _______, _______,              NK_TOGG, _______, KC_HOME, KC_END,
        _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______,
        _______, _______, _______,      _______, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______, _______,              _______, _______, _______, _______,
        _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,              _______, _______, _______,
        _______,          _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,   KC_PGUP,   _______, _______, _______, _______,
        _______, _______, _______,                                 _______,                            _______, KC_APP,  _______,   KC_HOME, KC_PGDN, KC_END,    _______, _______
    ),
};

void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_matrix = false;
    debug_keyboard = false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        int8_t r_val;

        switch (keycode) {
            case AP_UP:
                r_val = actuation_point_make_deeper();
                if (r_val >= 0) fc980c_config.actuation_point_value = r_val;
                fc980c_eeconfig_update_kb();
                break;
            case AP_DN:
                r_val = actuation_point_make_shallower();
                if (r_val >= 0) fc980c_config.actuation_point_value = r_val;
                fc980c_eeconfig_update_kb();
                break;
            case AP_RST:
                actuation_point_reset();
                eeconfig_init_kb();
                break;
            case AP_PRINT_VAL:
                dprintf("acutation_point (AD5258): rdac %"PRIu8", eeprom %"PRIu8"\n", actuation_point_read_rdac(), actuation_point_read_eeprom());
#ifdef SEND_STRING_ENABLE
                char rdac_buf[3];
                snprintf(rdac_buf, sizeof(rdac_buf), "%"PRIu8, actuation_point_read_rdac());
                send_string(rdac_buf);
#endif
                break;
            default:
                dprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time);
                break;
        }
    }

    return true;
}
