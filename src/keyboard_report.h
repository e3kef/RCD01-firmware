#pragma once

#include <stdint.h>

struct KeyboardReport
{
    uint8_t modifiers;
    uint8_t keycodes[6];
};
