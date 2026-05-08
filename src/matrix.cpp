#include "matrix.h"

#include "pico/stdlib.h"

static constexpr uint_fast8_t TEST_KEY_PIN_OUT = 5;     // need edit
static constexpr uint_fast8_t TEST_KEY_PIN_IN = 9;

void matrix_init(){
    gpio_init(TEST_KEY_PIN_OUT);
    gpio_init(TEST_KEY_PIN_IN);
    gpio_set_dir(TEST_KEY_PIN_OUT, GPIO_OUT);
    gpio_set_dir(TEST_KEY_PIN_IN, GPIO_IN);
    // gpio_put(TEST_KEY_PIN_IN, 1);
    gpio_pull_up(TEST_KEY_PIN_IN);
    // gpio_pull_down(TEST_KEY_PIN_IN);
}

void matrix_task(){

}

bool test_key_pressed(){
    bool result = false;
    gpio_put(TEST_KEY_PIN_OUT, 0);
    if(!gpio_get(TEST_KEY_PIN_IN)){
        result = true;
    }
    return result;
}
