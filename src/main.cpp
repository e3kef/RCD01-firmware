#include <stdio.h>
#include "pico/stdlib.h"

#include "matrix.h"
#include "keymap.h"
#include "transport.h"


int main()
{
    stdio_init_all();

    matrix_init();
    transport_init();

    bool previous_pressed = false;

    while (true) {
        transport_task();
        matrix_task();

        bool current_pressed = matrix_is_test_key_pressed();

        if(current_pressed != previous_pressed){
            if(current_pressed){
                KeyboardReport report = keymap_make_report(true);
                transport_send_report(report);
            }else{
                transport_send_release();
            }

            previous_pressed = current_pressed;
        }

        sleep_ms(3);
    }
}
