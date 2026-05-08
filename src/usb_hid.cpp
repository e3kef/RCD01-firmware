#include "usb_hid.h"

#include "bsp/board_api.h"
#include "tusb.h"

void usb_hid_init(){
    board_init();
    tusb_init(BOARD_TUD_RHPORT);
}

void usb_hid_task(){
    tud_task();
}

bool usb_hid_ready(){
    return tud_mounted() && tud_hid_ready();
}

bool usb_hid_send_report(const KeyboardReport& report){
    if(!usb_hid_ready()){
        return false;
    }

    return tud_hid_keyboard_report(
        0,
        report.modifires,
        report.keycodes
    );
}

bool usb_hid_send_release(){
    if(!usb_hid_ready()){
        return false;
    }

    return tud_hid_keyboard_report(
        0,
        0,
        nullptr
    );
}