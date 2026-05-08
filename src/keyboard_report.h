#pragma once

#include <stdint.h>

struct KeyboardReport
{
    uint8_t modifires;
    uint8_t keycodes[6];
};
