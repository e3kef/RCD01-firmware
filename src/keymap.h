#pragma once

#include "tusb.h"

#include "keyboard_report.h"
#include "matrix.h"

inline constexpr uint8_t KEYMAP_HID[73] = {
    HID_KEY_NONE,    // 0: KEY_NONE

    HID_KEY_7,       // 1
    HID_KEY_8,       // 2
    HID_KEY_9,       // 3
    HID_KEY_4,       // 4
    HID_KEY_5,       // 5
    HID_KEY_6,       // 6
    HID_KEY_1,       // 7
    HID_KEY_2,       // 8
    HID_KEY_3,       // 9
    HID_KEY_KEYPAD_ADD,     // 10
    HID_KEY_MINUS,   // 11
    HID_KEY_0,       // 12

    HID_KEY_ESCAPE,  // 13
    HID_KEY_Q,       // 14
    HID_KEY_W,       // 15
    HID_KEY_E,       // 16
    HID_KEY_R,       // 17
    HID_KEY_T,       // 18
    HID_KEY_Y,       // 19
    HID_KEY_U,       // 20
    HID_KEY_I,       // 21
    HID_KEY_O,       // 22
    HID_KEY_P,       // 23
    HID_KEY_NONE,    // 24

    HID_KEY_TAB,     // 25
    HID_KEY_A,       // 26
    HID_KEY_S,       // 27
    HID_KEY_D,       // 28
    HID_KEY_F,       // 29
    HID_KEY_G,       // 30
    HID_KEY_H,       // 31
    HID_KEY_J,       // 32
    HID_KEY_K,       // 33
    HID_KEY_L,       // 34
    HID_KEY_SEMICOLON,       // 35
    HID_KEY_KEYPAD_COLON,    // 36

    HID_KEY_SHIFT_LEFT,      // 37
    HID_KEY_Z,       // 38
    HID_KEY_X,       // 39
    HID_KEY_C,       // 40
    HID_KEY_V,       // 41
    HID_KEY_B,       // 42
    HID_KEY_N,       // 43
    HID_KEY_M,       // 44
    HID_KEY_COMMA,       // 45
    HID_KEY_PERIOD,      // 46
    HID_KEY_SLASH,       // 47
    HID_KEY_ARROW_UP,    // 48

    HID_KEY_ESCAPE,  // 49 funciton 実装あとで検討
    HID_KEY_ALT_LEFT,    // 50
    HID_KEY_LANG2,       // 51 EN?
    HID_KEY_CONTROL_LEFT,    // 52
    HID_KEY_R,       // 53 CLI 実装あとで検討
    HID_KEY_SPACE,       // 54
    HID_KEY_ENTER,       // 55
    HID_KEY_KANJI2,      // 56 JP?
    HID_KEY_GUI_RIGHT,    // 57 win?
    HID_KEY_NONE,    // 58
    HID_KEY_NONE,    // 59
    HID_KEY_NONE,    // 60

    HID_KEY_BACKSPACE,       // 61
    HID_KEY_HOME,            // 62
    HID_KEY_DELETE,          // 63
    HID_KEY_END,             // 64
    HID_KEY_SHIFT_RIGHT,     // 65
    HID_KEY_ARROW_LEFT,      // 66
    HID_KEY_ARROW_DOWN,      // 67
    HID_KEY_ARROW_RIGHT,     // 68
    HID_KEY_NONE,    // 69
    HID_KEY_NONE,    // 70
    HID_KEY_NONE,    // 71
    HID_KEY_NONE,    // 72
};

KeyboardReport keymap_make_report();