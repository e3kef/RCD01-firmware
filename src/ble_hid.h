#pragma once

#include "keyboard_report.h"

void ble_hid_init();
void ble_hid_task();
bool ble_hid_ready();

bool ble_hid_send_report(const KeyboardReport& report);
bool ble_hid_send_release();