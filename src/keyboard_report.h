#pragma once

#include <stdint.h>

struct KeyboardReport
{
    uint_fast8_t modifires;
    uint_fast8_t keycodes[6];
};
