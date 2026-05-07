#include "usb_hid.h"

#include "bsp/board_api.h"
#include "tusb.h"

void usb_hid_init(){
    board_init();
    tusb_init();
}