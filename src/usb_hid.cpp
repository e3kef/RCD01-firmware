#include "usb_hid.h"

#include "bsp/board_api.h"
#include "tusb.h"

void usb_hid_init(){
    board_init();
    tusb_init(BOARD_TUD_RHPORT, &dev_init);
}

void usb_hid_task(){
    tud_task();
}

bool usb_hid_ready(){
    return tud_mounted() && tud_hid_ready();
}