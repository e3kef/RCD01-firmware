#include "keymap.h"

#include "tusb.h"

static bool hid_key_to_modifier(uint8_t hid_key, uint8_t& modifier){
    switch(hid_key){
        case HID_KEY_CONTROL_LEFT:
            modifier = 0x01;
            return true;
        case HID_KEY_SHIFT_LEFT:
            modifier = 0x02;
            return true;
        case HID_KEY_ALT_LEFT:
            modifier = 0x04;
            return true;
        case HID_KEY_GUI_LEFT:
            modifier = 0x08;
            return true;
        case HID_KEY_CONTROL_RIGHT:
            modifier = 0x10;
            return true;
        case HID_KEY_SHIFT_RIGHT:
            modifier = 0x20;
            return true;
        case HID_KEY_ALT_RIGHT:
            modifier = 0x40;
            return true;
        case HID_KEY_GUI_RIGHT:
            modifier = 0x80;
            return true;
        default:
            modifier = 0;
            return false;
    }
}

static KeyAction resolve_key_action(uint8_t key_id){
    const bool fn_pressed = matrix_pressed(KEY_FN);
    const bool select_pressed = matrix_pressed(KEY_SELECT_LAYER);

    if(fn_pressed){
        const KeyAction fn_action = KEYMAP_FN[key_id];
        if(fn_action.key != KEY_TRANSPARENT){
            return fn_action;
        }
    }

    if(select_pressed){
        const KeyAction select_action = KEYMAP_LAYER[key_id];
        if(select_action.key != KEY_TRANSPARENT){
            return select_action;
        }
    }

    return KEYMAP_BASE[key_id];
}

KeyboardReport keymap_make_report(){
    KeyboardReport report{};
    report.modifiers = 0;

    for(uint_fast8_t i = 0; i < 6; i++){
        report.keycodes[i] = 0;
    }

    uint8_t keycode_count = 0;

    for(uint8_t key_id = 1; key_id < MATRIX_KEY_COUNT; key_id++){
        if(!matrix_pressed(key_id)){
            continue;
        }

        if(key_id == KEY_FN || key_id == KEY_SELECT_LAYER){
            continue;
        }

        const KeyAction action = resolve_key_action(key_id);

        if(action.key == HID_KEY_NONE || action.key == KEY_TRANSPARENT){
            continue;
        }

        report.modifiers |= action.mods;

        uint8_t modifier = 0;
        if(hid_key_to_modifier(action.key, modifier)){
            report.modifiers |= modifier;
            continue;
        }

        if(keycode_count < 6){
            report.keycodes[keycode_count] = action.key;
            keycode_count++;
        }
    }

    return report;
}
