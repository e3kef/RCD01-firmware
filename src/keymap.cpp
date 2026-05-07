#include "keymap.h"

#include "tusb.h"

KeyboardReport keymap_make_report(bool test_key_pressed){
    KeyboardReport report{};
    report.modifires = 0;

    for(uint_fast8_t i = 0; i < 6; i++){
        report.keycodes[i] = 0;
    }

    if(test_key_pressed){
        report.keycodes[0] = HID_KEY_A;
    }

    return report;
}