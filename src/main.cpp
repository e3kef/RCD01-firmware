#include <stdio.h>

#include "pico/stdlib.h"

#include "matrix.h"
#include "keymap.h"
#include "transport.h"


int main(){
    stdio_init_all();

    matrix_init();
    transport_init();

    bool report_sent = false;

    while (true) {
        transport_task();
        matrix_task();

        if(matrix_has_pressed_key()){
            if(matrix_changed() || !report_sent){
                KeyboardReport report = keymap_make_report();

                if(transport_send_report(report)){
                    report_sent = true;
                }
            }
        }else{
            if(report_sent){
                if(transport_send_release()){
                    report_sent = false;
                }
            }
        }
        
        sleep_ms(5);
    }
}
