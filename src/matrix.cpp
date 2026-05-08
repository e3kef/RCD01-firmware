#include <stdint.h>
#include <string.h>
#include "pico/stdlib.h"

#include "matrix.h"

static bool current_keys[MATRIX_KEY_COUNT] = {};
static bool previous_keys[MATRIX_KEY_COUNT] = {};

void matrix_init(){
    for(uint8_t i = 0; i < MATRIX_ROW_COUNT; i++){
        gpio_init(ROWS[i].gpio);
        gpio_set_dir(ROWS[i].gpio, GPIO_IN);
        gpio_pull_up(ROWS[i].gpio);
    }

    for(uint8_t i = 0; i < MATRIX_COL_COUNT; i++){
        gpio_init(COLS[i].gpio);
        gpio_set_dir(COLS[i].gpio, GPIO_OUT);
        gpio_put(COLS[i].gpio, 1);
    }
}

void matrix_task(){
    memcpy(previous_keys, current_keys, sizeof(current_keys));
    memset(current_keys, 0, sizeof(current_keys));

    for(uint8_t col = 0; col < MATRIX_COL_COUNT; col++){
        gpio_put(COLS[col].gpio, 0);
        sleep_us(5);

        for(uint8_t row = 0; row < MATRIX_ROW_COUNT; row++){
            const uint8_t key_id = KEY_ID[row][col];

            if(key_id == KEY_NONE || key_id >= MATRIX_KEY_COUNT){
                continue;
            }

            if(!gpio_get(ROWS[row].gpio)){
                current_keys[key_id] = true;
            }
        }

        gpio_put(COLS[col].gpio, 1);
    }
}

bool matrix_pressed(uint8_t key_id){
    if(key_id >= MATRIX_KEY_COUNT){
        return false;
    }

    return current_keys[key_id];
}

bool matrix_has_pressed_key(){
    for(uint8_t key_id = 1; key_id < MATRIX_KEY_COUNT; key_id++){
        if(current_keys[key_id]){
            return true;
        }
    }

    return false;
}

bool matrix_changed(){
    for(uint8_t key_id = 1; key_id < MATRIX_KEY_COUNT; key_id++){
        if(current_keys[key_id] != previous_keys[key_id]){
            return true;
        }
    }

    return false;
}
