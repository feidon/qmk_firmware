/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum charybdis_keymap_layers {
    _BASE = 0,
    _COL = 1,
    _NUM = 2,
    _NAV = 3,
    _MOU = 4,
};

#define CTL_TAB LCTL_T(KC_TAB)

#define CTL_A LCTL_T(KC_A)
#define GUI_S LGUI_T(KC_S)
#define GUI_R LGUI_T(KC_R)
#define ALT_D LALT_T(KC_D)
#define ALT_S LALT_T(KC_S)
#define SFT_F LSFT_T(KC_F)
#define SFT_TT LSFT_T(KC_T)

#define SFT_J RSFT_T(KC_J)
#define SFT_N RSFT_T(KC_N)
#define ALT_K LALT_T(KC_K)
#define ALT_E LALT_T(KC_E)
#define GUI_L LGUI_T(KC_L)
#define GUI_I LGUI_T(KC_I)
#define CTL_SCL LCTL_T(KC_SCLN)
#define CTL_O LCTL_T(KC_O)

#define NAV_Z LT(_NAV, KC_Z)
#define NAV_SL LT(_NAV, KC_SLSH)

#define SFT_1 LSFT(KC_1)
#define SFT_2 LSFT(KC_2)
#define SFT_3 LSFT(KC_3)
#define SFT_4 LSFT(KC_4)
#define SFT_5 LSFT(KC_5)
#define SFT_6 LSFT(KC_6)
#define SFT_7 LSFT(KC_7)
#define SFT_8 LSFT(KC_8)
#define SFT_9 LSFT(KC_9)
#define SFT_0 LSFT(KC_0)

#define SFT_EQL LSFT(KC_EQL)
#define SFT_MINS LSFT(KC_MINS)
#define SFT_QUOT LSFT(KC_QUOT)
#define SFT_LBRC LSFT(KC_LBRC)
#define SFT_RBRC LSFT(KC_RBRC)

#define ALT_UP LALT(KC_UP)
#define ALT_DOWN LALT(KC_DOWN)

#define VOL_UP KC_KB_VOLUME_UP
#define VOL_DOWN KC_KB_VOLUME_DOWN

enum combos {
    CV_TAB,
    MCOM_ENT,
    QW_ESC
};

// Tap Dance keycodes
enum td_keycodes {
    SFT1_CTL,
    SFT2_GUI,
    SFT3_ALT,
    SFT4_SFT,
    SFT0_CTL,
    SFT9_GUI,
    SFT8_ALT,
    SFT7_SFT,
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;

static td_state_t td_state;
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}
void altlp_finished(tap_dance_state_t *state, void *user_data);
void altlp_reset(tap_dance_state_t *state, void *user_data);

#define TD1 TD(SFT1_CTL)
#define TD2 TD(SFT2_GUI)
#define TD3 TD(SFT3_ALT)
#define TD4 TD(SFT4_SFT)
#define TD0 TD(SFT0_CTL)
#define TD9 TD(SFT9_GUI)
#define TD8 TD(SFT8_ALT)
#define TD7 TD(SFT7_SFT)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        CTL_A,    GUI_S,   ALT_D,   SFT_F,   KC_G,     KC_H,   SFT_J,   ALT_K,   GUI_L, CTL_SCL,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        NAV_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M, KC_COMM,  KC_DOT,  NAV_SL,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
        DF(_COL), KC_ENT,  KC_SPC,    MO(_NUM),MO(_NAV),DF(_COL)
  // ╰───────────────────────────╯   ╰───────────────────────────╯
    ),

    [_COL] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,     KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        CTL_A,   GUI_R,   ALT_S,  SFT_TT,   KC_D,     KC_H,   SFT_N,   ALT_E,   GUI_I,   CTL_O,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        NAV_Z,   KC_X,    KC_C,    KC_V,    KC_B,     KC_K,    KC_M, KC_COMM,  KC_DOT,  NAV_SL,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
        DF(_BASE),KC_ENT,KC_SPC,      MO(_NUM),MO(_NAV),DF(_BASE)
  // ╰───────────────────────────╯   ╰───────────────────────────╯
    ),

    [_NUM] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        TD1,     TD2,     TD3,     TD4,    SFT_5,      SFT_6,     TD7,     TD8,     TD9,     TD0,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        SFT_LBRC,SFT_RBRC, KC_LBRC, KC_RBRC,SFT_QUOT,  KC_QUOT,SFT_MINS, KC_MINS, SFT_EQL,  KC_EQL,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
        _______, _______,  KC_DEL,    _______, _______, _______
  // ╰───────────────────────────╯   ╰───────────────────────────╯
    ),
    [_NAV] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        KC_GRV,  KC_HOME,   KC_UP,  KC_END, KC_PGUP,    KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_BSLS,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        CG_TOGG, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,    KC_F5,   KC_F6,   KC_F7,   KC_F8, _______,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        VOL_DOWN, VOL_UP,ALT_DOWN,  ALT_UP, _______,    KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
        _______, _______,  _______,   _______, _______, _______
  // ╰───────────────────────────╯   ╰───────────────────────────╯
    ),
    [_MOU] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        _______, _______, _______, MS_BTN1, MS_BTN2,  MS_BTN1, MS_BTN2, _______, _______, _______,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
        _______, _______, _______,    _______, _______, _______
  // ╰───────────────────────────╯   ╰───────────────────────────╯
    ),
};
// clang-format on

void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD1:
        case TD2:
        case TD3:
        case TD4:
        case TD0:
        case TD9:
        case TD8:
        case TD7:
            return 120;
        default:
            return TAPPING_TERM;
    }
}

//{ Combos
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM mcom_combo[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};

combo_t key_combos[] = {
    [CV_TAB] = COMBO(cv_combo, KC_TAB),
    [MCOM_ENT]  = COMBO(mcom_combo, KC_ENT),
    [QW_ESC] = COMBO(qw_combo, KC_ESC),
};
//}

//{ TapDances
void sft1ctl_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(LSFT(KC_1));
            break;
        case TD_SINGLE_HOLD:
            register_code16(keycode_config(KC_LCTL));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(LSFT(KC_1));
            register_code16(LSFT(KC_1));
            break;
        default:
            break;
    }
}

void sft1ctl_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(LSFT(KC_1));
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(keycode_config(KC_LCTL));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(LSFT(KC_1));
            break;
        default:
            break;
    }
}

void sft2gui_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(LSFT(KC_2));
            break;
        case TD_SINGLE_HOLD:
            register_code16(keycode_config(KC_LGUI));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(LSFT(KC_2));
            register_code16(LSFT(KC_2));
            break;
        default:
            break;
    }
}

void sft2gui_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(LSFT(KC_2));
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(keycode_config(KC_LGUI));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(LSFT(KC_2));
            break;
        default:
            break;
    }
}

void sft3alt_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(LSFT(KC_3));
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(LSFT(KC_3));
            register_code16(LSFT(KC_3));
            break;
        default:
            break;
    }
}

void sft3alt_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(LSFT(KC_3));
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(LSFT(KC_3));
            break;
        default:
            break;
    }
}

void sft4sft_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(LSFT(KC_4));
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(LSFT(KC_4));
            register_code16(LSFT(KC_4));
            break;
        default:
            break;
    }
}

void sft4sft_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(LSFT(KC_4));
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(LSFT(KC_4));
            break;
        default:
            break;
    }
}

void sft0ctl_finished(tap_dance_state_t *state, void *user_data){
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(LSFT(KC_0));
            break;
        case TD_SINGLE_HOLD:
            register_code16(keycode_config(KC_LCTL));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(LSFT(KC_0));
            register_code16(LSFT(KC_0));
            break;
        default:
            break;
    }
}

void sft0ctl_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(LSFT(KC_0));
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(keycode_config(KC_LCTL));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(LSFT(KC_0));
            break;
        default:
            break;
    }
}

void sft9gui_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(LSFT(KC_9));
            break;
        case TD_SINGLE_HOLD:
            register_code16(keycode_config(KC_LGUI));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(LSFT(KC_9));
            register_code16(LSFT(KC_9));
            break;
        default:
            break;
    }
}

void sft9gui_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(LSFT(KC_9));
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(keycode_config(KC_LGUI));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(LSFT(KC_9));
            break;
        default:
            break;
    }
}

void sft8alt_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(LSFT(KC_8));
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(LSFT(KC_8));
            register_code16(LSFT(KC_8));
            break;
        default:
            break;
    }
}

void sft8alt_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(LSFT(KC_8));
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(LSFT(KC_8));
            break;
        default:
            break;
    }
}

void sft7sft_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(LSFT(KC_7));
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(LSFT(KC_7));
            register_code16(LSFT(KC_7));
            break;
        default:
            break;
    }
}

void sft7sft_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(LSFT(KC_7));
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(LSFT(KC_7));
            break;
        default:
            break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [SFT1_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft1ctl_finished, sft1ctl_reset),
    [SFT2_GUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft2gui_finished, sft2gui_reset),
    [SFT3_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft3alt_finished, sft3alt_reset),
    [SFT4_SFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft4sft_finished, sft4sft_reset),
    [SFT7_SFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft7sft_finished, sft7sft_reset),
    [SFT8_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft8alt_finished, sft8alt_reset),
    [SFT9_GUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft9gui_finished, sft9gui_reset),
    [SFT0_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft0ctl_finished, sft0ctl_reset),
};
//}
