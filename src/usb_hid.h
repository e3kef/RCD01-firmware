#pragma once

#include "keyboard_report.h"

void usb_hid_init();
void usb_hid_task();
bool usb_hid_ready();

bool usb_hid_send_report(const KeyboardReport& report);
bool usb_hid_send_release();

