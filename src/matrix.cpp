#include "matrix.h"

#include "pico/stdlib.h"

static constexpr uint TEST_KEY_PIN = 8;     // need edit

vid matrix_init(){
    gpio_init(TEST_KEY_PIN);
    gpio_set_d
}