#pragma once

#include "keyboard_report.h"

void transport_init();
void transport_task();
bool transport_ready();

bool transport_send_report(const KeyboardReport& report);
bool transport_send_release();