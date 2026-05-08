#include "transport.h"

#include "usb_hid.h"
#include "ble_hid.h"

void transport_init(){
    usb_hid_init();
    // ble_hid_init();
}

void transport_task(){
    usb_hid_task();
    // ble_hid_task();
}

bool transport_ready(){
    return usb_hid_ready(); // || ble_hid_ready();
}

bool transport_send_report(const KeyboardReport& report){
    if(!usb_hid_ready()){
        return false;
    } 

    return usb_hid_send_report(report);
}

bool transport_send_release(){
    if(!usb_hid_ready()){
        return false;
    }

    return usb_hid_send_release();
}
