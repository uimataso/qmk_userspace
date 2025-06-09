#include QMK_KEYBOARD_H

// clang-format off
enum layers_names {
    _DEF_,
    _SYM_,
    _NUM_,
    _NAV_,
    _FUN_,
};

enum custom_keycodes {
    KEYCODE = SAFE_RANGE,

    // String
    ST_HELP,
};

enum custom_keycodes_shortcut {
    SYM_SPC = LT(_SYM_, KC_SPC),
    NUM_ENT = LT(_NUM_, KC_ENT),

    // Move one word
    CK_LW = C(KC_LEFT),
    CK_RW = C(KC_RIGHT),

    // Move focus on browser tabs
    CK_LTAB = C(S(KC_TAB)),
    CK_RTAB = C(KC_TAB),

    // Set different layout
    TO_DEF = TO(_DEF_),

    // Home Row Mod
    HM_A = LGUI_T(KC_A), HM_S = LALT_T(KC_S), HM_D = LCTL_T(KC_D), HM_F = LSFT_T(KC_F),
    HM_J = RSFT_T(KC_J), HM_K = RCTL_T(KC_K), HM_L = RALT_T(KC_L), HM_P = RGUI_T(KC_P),

    NA_V = LT(_NAV_, KC_V),

    S_LEFT = S(KC_LEFT),
    S_DOWN = S(KC_DOWN),
    S_UP   = S(KC_UP),
    S_RGHT = S(KC_RGHT),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF_] = LAYOUT(
        XXXXXXX, KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    XXXXXXX,
        HM_A,    HM_S,    HM_D,    HM_F,    KC_G,         KC_H,    HM_J,    HM_K,    HM_L,    HM_P,
        KC_UNDS, KC_X,    KC_C,    NA_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                                 MO(_NAV_), SYM_SPC,      NUM_ENT, OSM(MOD_LSFT)
    ),

    [_SYM_] = LAYOUT(
        XXXXXXX, KC_TILD, KC_LT,   KC_GT,   KC_TILD,      KC_CIRC, KC_LCBR, KC_RCBR, KC_DLR,  XXXXXXX,
        KC_CIRC, KC_DLR,  KC_QUES, KC_EXLM, KC_GRV,       KC_AMPR, KC_LPRN, KC_RPRN, KC_SCLN, KC_PERC,
        KC_UNDS, C(KC_X), C(KC_C), C(KC_V), KC_AT,        _______, KC_LBRC, KC_RBRC, KC_HASH, KC_BSLS,
                                   _______, _______,      _______, _______
    ),

    [_NUM_] = LAYOUT(
        XXXXXXX, KC_7,    KC_8,    KC_9,    KC_TILD,      KC_PIPE, KC_CIRC, KC_ASTR, KC_SLSH, XXXXXXX,
        KC_GT,   KC_4,    KC_5,    KC_6,    KC_0,         KC_AMPR, KC_PLUS, KC_MINS, KC_EQL,  KC_PERC,
        KC_LT,   KC_1,    KC_2,    KC_3,    KC_EXLM,      _______, KC_RBRC, KC_LBRC, KC_COMM, KC_DOT,
                                   _______, _______,      _______, _______
    ),

    [_NAV_] = LAYOUT(
        XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F10,       KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
        KC_PSCR, KC_F4,   KC_F5,   KC_F6,   KC_F11,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,       S_LEFT,  S_DOWN,  S_UP,    S_RGHT, _______,
                                   XXXXXXX, _______,      _______, XXXXXXX
    ),

    [_FUN_] = LAYOUT(
        XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F10,       KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
        KC_PSCR, KC_F4,   KC_F5,   KC_F6,   KC_F11,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,       S_LEFT,  S_DOWN,  S_UP,    S_RGHT, _______,
                                   XXXXXXX, _______,      _______, XXXXXXX
    ),
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
                       '*', '*',  '*', '*'
    );

// clang-format on

/* Create Combos */
#undef COMB
#define COMB(name, key, ...) name,
enum combos {
#include "combos.def"
};

#undef COMB
#define COMB(name, key, ...) const uint16_t PROGMEM cmb_##name[] = {__VA_ARGS__, COMBO_END};
#include "combos.def"

#undef COMB
#define COMB(name, key, ...) [name] = COMBO(cmb_##name, key),
combo_t key_combos[] = {
#include "combos.def"
};

uint16_t COMBO_LEN = sizeof(key_combos) / sizeof(*key_combos);

uint8_t combo_ref_from_layer(uint8_t layer) {
    return layer; // important if default is not in case.
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (combo_index) {
        /* Enable def combo if def layer is enable */
        case DEFAULT_COMBO_START ... DEFAULT_COMBO_END:
            if (layer_state_is(_DEF_)) return true;
    }

    return false;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_MINS:
        case KC_UNDS:
        case KC_BSPC:
        case KC_DEL:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Tri Layer Implementation
        case SYM_SPC:
            if (record->event.pressed)
                layer_on(_FUN_);
            else
                layer_off(_FUN_);
            update_tri_layer(_SYM_, _NUM_, _FUN_);
            // return false;
            return true;
        case NUM_ENT:
            if (record->event.pressed)
                layer_on(_NUM_);
            else
                layer_off(_NUM_);
            update_tri_layer(_SYM_, _NUM_, _FUN_);
            // return false;
            return true;
    }

    if (record->event.pressed) {
        // clang-format off
        switch (keycode) {
            case ST_HELP:
                SEND_STRING(" --help"); return false; break;
        }
        // clang-format on
    }

    return true;
}
