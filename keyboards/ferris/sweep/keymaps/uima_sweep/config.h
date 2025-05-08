#pragma once

// Tap Hold
#define TAPPING_TERM 140
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM 0 /* Set to 0 to disable the Quick Tap Term that repeate the key when user holds a key after tapping it */

// Combo
// #define COMBO_COUNT 17
#define COMBO_TERM 30

// Caps Word
#define CAPS_WORD_INVERT_ON_SHIFT
#define CAPS_WORD_IDLE_TIMEOUT 3000

// Oneshot
#define ONESHOT_TAP_TOGGLE 0 /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 1500 /* Time (in ms) before the one shot key is released */
