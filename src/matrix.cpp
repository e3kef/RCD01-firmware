#include "matrix.h"

#include "pico/stdlib.h"

static constexpr uint_fast8_t TEST_KEY_PIN_OUT = 8;     // need edit
static constexpr uint_fast8_t TEST_KEY_PIN_IN = 5;

void matrix_init(){
    gpio_init(TEST_KEY_PIN_OUT);
    gpio_init(TEST_KEY_PIN_IN);
    gpio_set_dir(TEST_KEY_PIN_OUT, GPIO_OUT);
    gpio_set_dir(TEST_KEY_PIN_OUT, GPIO_IN);
    gpio_put(TEST_KEY_PIN_OUT, 1);
    gpio_pull_down(TEST_KEY_PIN_IN);
}

void matrix_task(){

}

bool matrix_is_test_key_pressed(){
    return gpio_get(TEST_KEY_PIN_IN) != 0;
}
