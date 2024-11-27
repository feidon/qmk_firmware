/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum dilemma_keymap_layers {
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

// Tap Dance keycodes
enum td_keycodes {
    SFT1_CTL // Our example key: `LALT` when held, `(` when tapped. Add additional keycodes for each tapdance.
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void altlp_finished(tap_dance_state_t *state, void *user_data);
void altlp_reset(tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BACKSPACE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CTL_TAB,   CTL_A,   GUI_S,   ALT_D,   SFT_F,    KC_G,                         KC_H,   SFT_J,   ALT_K,   GUI_L, CTL_SCL,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   NAV_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT,  NAV_SL, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         DF(_COL),  KC_ENT,  KC_SPC,   MO(_NUM),MO(_NAV), DF(_COL)
                                      //`--------------------------'  `--------------------------'
  ),

    [_COL] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BACKSPACE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CTL_TAB,   CTL_A,   GUI_R,   ALT_S,  SFT_TT,    KC_D,                         KC_H,   SFT_N,   ALT_E,   GUI_I,   CTL_O,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   NAV_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT,  NAV_SL, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        DF(_BASE),  KC_ENT,  KC_SPC,   MO(_NUM),  KC_DEL,DF(_BASE)
                                      //`--------------------------'  `--------------------------'
  ),

    [_NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,TD(SFT1_CTL),SFT_2,   SFT_3,   SFT_4,   SFT_5,                        SFT_6,   SFT_7,   SFT_8,   SFT_9,   SFT_0, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,SFT_LBRC,SFT_RBRC, KC_LBRC, KC_RBRC,SFT_QUOT,                      KC_QUOT,SFT_MINS, KC_MINS, SFT_EQL,  KC_EQL, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,  KC_GRV, KC_HOME,   KC_UP,  KC_END, KC_PGUP,                        KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_BSLS, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, CG_TOGG, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                        KC_F5,   KC_F6,   KC_F7,   KC_F8, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,VOL_DOWN,  VOL_UP,ALT_DOWN,  ALT_UP, _______,                        KC_F9,  KC_F10,  KC_F11,  KC_F12, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:

void sft1ctl_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(LSFT(KC_1));
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
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
            unregister_mods(MOD_BIT(KC_LCTL)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(LSFT(KC_1));
            break;
        default:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
tap_dance_action_t tap_dance_actions[] = {
    [SFT1_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft1ctl_finished, sft1ctl_reset)
};
