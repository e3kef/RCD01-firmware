#pragma once

#include "tusb.h"

#include "keyboard_report.h"
#include "matrix.h"

struct KeyAction
{
    uint8_t key;
    uint8_t mods;
};

inline constexpr uint8_t MOD_LSHIFT = 0x02;
inline constexpr uint8_t MOD_LGUI = 0x08;
inline constexpr uint8_t MOD_RSHIFT = 0x20;
inline constexpr uint8_t MOD_RCTRL = 0x10;

inline constexpr uint8_t KEY_SELECT_LAYER = 53;

inline constexpr uint8_t KEY_TRANSPARENT = 0xff;

inline constexpr uint8_t KEY_FN = 49;
inline constexpr uint8_t KEY_LSHIFT = 37;
inline constexpr uint8_t KEY_RSHIFT = 65;

// key code
inline constexpr KeyAction KC(uint8_t key){
    return {key, 0};
}

// key with modifier
inline constexpr KeyAction KM(uint8_t key, uint8_t mods) {
    return {key, mods};
}

// transparent
inline constexpr KeyAction TRNS(){
    return {KEY_TRANSPARENT, 0};
}

inline constexpr KeyAction KEYMAP_BASE[MATRIX_KEY_COUNT] = {
    KC(HID_KEY_NONE),    // 0: KEY_NONE

    KC(HID_KEY_7),       // 1
    KC(HID_KEY_8),       // 2
    KC(HID_KEY_9),       // 3
    KC(HID_KEY_4),       // 4
    KC(HID_KEY_5),       // 5
    KC(HID_KEY_6),       // 6
    KC(HID_KEY_1),       // 7
    KC(HID_KEY_2),       // 8
    KC(HID_KEY_3),       // 9
    KC(HID_KEY_KEYPAD_ADD),     // 10
    KC(HID_KEY_MINUS),   // 11
    KC(HID_KEY_0),       // 12

    KC(HID_KEY_ESCAPE),  // 13
    KC(HID_KEY_Q),       // 14
    KC(HID_KEY_W),       // 15
    KC(HID_KEY_E),       // 16
    KC(HID_KEY_R),       // 17
    KC(HID_KEY_T),       // 18
    KC(HID_KEY_Y),       // 19
    KC(HID_KEY_U),       // 20
    KC(HID_KEY_I),       // 21
    KC(HID_KEY_O),       // 22
    KC(HID_KEY_P),       // 23
    KC(HID_KEY_NONE),    // 24

    KC(HID_KEY_TAB),     // 25
    KC(HID_KEY_A),       // 26
    KC(HID_KEY_S),       // 27
    KC(HID_KEY_D),       // 28
    KC(HID_KEY_F),       // 29
    KC(HID_KEY_G),       // 30
    KC(HID_KEY_H),       // 31
    KC(HID_KEY_J),       // 32
    KC(HID_KEY_K),       // 33
    KC(HID_KEY_L),       // 34
    KC(HID_KEY_SEMICOLON),       // 35
    KC(HID_KEY_KEYPAD_COLON),    // 36

    KC(HID_KEY_SHIFT_LEFT),      // 37
    KC(HID_KEY_Z),       // 38
    KC(HID_KEY_X),       // 39
    KC(HID_KEY_C),       // 40
    KC(HID_KEY_V),       // 41
    KC(HID_KEY_B),       // 42
    KC(HID_KEY_N),       // 43
    KC(HID_KEY_M),       // 44
    KC(HID_KEY_COMMA),       // 45
    KC(HID_KEY_PERIOD),      // 46
    KC(HID_KEY_SLASH),       // 47
    KC(HID_KEY_ARROW_UP),    // 48

    KC(HID_KEY_GUI_LEFT),    // 49 本来はfunciton 実装あとで検討
    KC(HID_KEY_ALT_LEFT),    // 50
    KC(HID_KEY_LANG2),       // 51 EN?
    KC(HID_KEY_CONTROL_LEFT),    // 52
    KC(HID_KEY_NONE),        // 53 本来はCLI 実装あとで検討
    KC(HID_KEY_SPACE),       // 54
    KC(HID_KEY_ENTER),       // 55
    KC(HID_KEY_KANJI2),      // 56 JP?
    KC(HID_KEY_GUI_RIGHT),    // 57 win?
    KC(HID_KEY_NONE),    // 58
    KC(HID_KEY_NONE),    // 59
    KC(HID_KEY_NONE),    // 60

    KC(HID_KEY_BACKSPACE),       // 61
    KC(HID_KEY_HOME),            // 62
    KC(HID_KEY_DELETE),          // 63
    KC(HID_KEY_END),             // 64
    KC(HID_KEY_SHIFT_RIGHT),     // 65
    KC(HID_KEY_ARROW_LEFT),      // 66
    KC(HID_KEY_ARROW_DOWN),      // 67
    KC(HID_KEY_ARROW_RIGHT),     // 68
    KC(HID_KEY_NONE),    // 69
    KC(HID_KEY_NONE),    // 70
    KC(HID_KEY_NONE),    // 71
    KC(HID_KEY_NONE),    // 72
};

// select layer
inline constexpr KeyAction KEYMAP_LAYER[MATRIX_KEY_COUNT] = {
    KC(HID_KEY_NONE),    // 0: KEY_NONE

    TRNS(),       // 1
    TRNS(),       // 2
    TRNS(),       // 3
    TRNS(),       // 4
    TRNS(),       // 5
    TRNS(),       // 6
    TRNS(),       // 7
    TRNS(),       // 8
    TRNS(),       // 9
    TRNS(),       // 10
    TRNS(),       // 11
    TRNS(),       // 12

    TRNS(),       // 13
    TRNS(),       // 14
    KM(HID_KEY_4, MOD_LSHIFT),       // 15
    KM(HID_KEY_5, MOD_LSHIFT),       // 16
    KM(HID_KEY_6, MOD_LSHIFT),       // 17
    KM(HID_KEY_7, MOD_LSHIFT),      // 18
    KC(HID_KEY_BRACKET_RIGHT),          // 19
    KC(HID_KEY_BACKSLASH),        // 20
    KM(HID_KEY_2, MOD_LSHIFT),       // 21
    KM(HID_KEY_MINUS, MOD_LSHIFT),   // 22
    KM(HID_KEY_KANJI3, MOD_LSHIFT),       // 23
    TRNS(),       // 24

    TRNS(),       // 25
    KC(HID_KEY_KANJI3),       // 26 en or backslash
    KC(HID_KEY_BRACKET_LEFT),       // 27
    KM(HID_KEY_BRACKET_LEFT, MOD_LSHIFT),               // 28
    KM(HID_KEY_EQUAL, MOD_LSHIFT),   // 29
    KC(HID_KEY_EQUAL),       // 30
    KM(HID_KEY_APOSTROPHE, MOD_LSHIFT),       // 31 *
    KM(HID_KEY_8, MOD_LSHIFT),       // 32 (
    KM(HID_KEY_9, MOD_LSHIFT),       // 33 )
    KM(HID_KEY_BRACKET_RIGHT, MOD_LSHIFT),       // 34 {
    KM(HID_KEY_BACKSLASH, MOD_LSHIFT),      // 35 }
    TRNS(),       // 36 

    TRNS(),       // 37
    TRNS(),       // 38
    TRNS(),       // 39
    KM(HID_KEY_COMMA, MOD_LSHIFT),       // 40
    KM(HID_KEY_PERIOD, MOD_LSHIFT),      // 41
    KM(HID_KEY_3, MOD_LSHIFT),       // 42
    KC(HID_KEY_MINUS),               // 43
    KM(HID_KEY_SEMICOLON, MOD_LSHIFT),       // 44
    TRNS(),       // 45
    KM(HID_KEY_1, MOD_LSHIFT),       // 46
    KM(HID_KEY_SLASH, MOD_LSHIFT),       // 47
    KM(HID_KEY_KANJI1, MOD_LSHIFT),       // 48

    TRNS(),       // 49
    TRNS(),       // 50
    TRNS(),       // 51
    TRNS(),       // 52
    TRNS(),       // 53
    TRNS(),       // 54
    TRNS(),       // 55
    TRNS(),       // 56
    TRNS(),       // 57
    TRNS(),       // 58
    TRNS(),       // 59
    TRNS(),       // 60

    TRNS(),       // 61
    TRNS(),       // 62
    TRNS(),       // 63
    TRNS(),       // 64
    TRNS(),       // 65
    TRNS(),       // 66
    TRNS(),       // 67
    TRNS(),       // 68
    TRNS(),       // 69
    TRNS(),       // 70
    TRNS(),       // 71
    TRNS()        // 72
};

// function layer
inline constexpr KeyAction KEYMAP_FN[MATRIX_KEY_COUNT] = {
    KC(HID_KEY_NONE),    // 0: KEY_NONE

    KC(HID_KEY_F7),       // 1
    KC(HID_KEY_F8),       // 2
    KC(HID_KEY_F9),       // 3
    KC(HID_KEY_F4),       // 4
    KC(HID_KEY_F5),       // 5
    KC(HID_KEY_F6),       // 6
    KC(HID_KEY_F1),       // 7
    KC(HID_KEY_F2),       // 8
    KC(HID_KEY_F3),       // 9
    KC(HID_KEY_F12),      // 10
    KC(HID_KEY_F11),      // 11
    KC(HID_KEY_F10),      // 12

    TRNS(),       // 13
    TRNS(),       // 14
    TRNS(),       // 15
    TRNS(),       // 16
    TRNS(),       // 17
    TRNS(),       // 18
    TRNS(),       // 19
    TRNS(),       // 20
    TRNS(),       // 21
    TRNS(),       // 22
    TRNS(),       // 23
    TRNS(),       // 24

    TRNS(),       // 25
    TRNS(),       // 26
    TRNS(),       // 27
    TRNS(),       // 28
    TRNS(),       // 29
    TRNS(),       // 30
    TRNS(),       // 31
    TRNS(),       // 32
    TRNS(),       // 33
    TRNS(),       // 34
    TRNS(),       // 35
    TRNS(),       // 36

    TRNS(),       // 37
    TRNS(),       // 38
    TRNS(),       // 39
    TRNS(),       // 40
    TRNS(),       // 41
    TRNS(),       // 42
    TRNS(),       // 43
    TRNS(),       // 44
    TRNS(),       // 45
    TRNS(),       // 46
    TRNS(),       // 47
    TRNS(),       // 48

    TRNS(),       // 49
    TRNS(),       // 50
    TRNS(),       // 51
    TRNS(),       // 52
    TRNS(),       // 53
    TRNS(),       // 54
    TRNS(),       // 55
    TRNS(),       // 56
    TRNS(),       // 57
    TRNS(),       // 58
    TRNS(),       // 59
    TRNS(),       // 60

    TRNS(),       // 61
    TRNS(),       // 62
    TRNS(),       // 63
    TRNS(),       // 64
    TRNS(),       // 65
    TRNS(),       // 66
    TRNS(),       // 67
    TRNS(),       // 68
    TRNS(),       // 69
    TRNS(),       // 70
    TRNS(),       // 71
    TRNS()        // 72
};

KeyboardReport keymap_make_report();
