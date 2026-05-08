#include <stdio.h>
#include "pico/stdlib.h"

#include "matrix.h"
#include "keymap.h"
#include "transport.h"


int main(){
    stdio_init_all();

    matrix_init();
    transport_init();

    bool previous_pressed = false;

    while (true) {
        transport_task();
        matrix_task();

        bool current_pressed = test_key_pressed();
        // bool current_pressed = false;

        // if(current_pressed == true){
        //     if(current_pressed != previous_pressed){
        //         KeyboardReport report = keymap_make_report(true);
        //         transport_send_report(report);               
        //     // }else{
        //     //     transport_send_release();
        //     // }
        //     }else{
        //     transport_send_release();
        //     }
        // }    

        if(current_pressed){
            if(current_pressed != previous_pressed){
                KeyboardReport report = keymap_make_report(true);
                if(transport_send_report(report)){
                    previous_pressed = true;
                }
            }
        }else{
            if(transport_send_release()){
                previous_pressed = false;
            }
        }
        
        // if(current_pressed != previous_pressed){
        //     if(current_pressed == true){
        //         KeyboardReport report = keymap_make_report(true);
        //         uint8_t send_report_counter = 0;
        //         while(!transport_send_report(report)){
        //             send_report_counter++;
        //             if(send_report_counter >= 10){
        //                 break;
        //             }
        //         }
        //     }else{
        //         uint8_t send_release_counter = 0;
        //         while(!transport_send_release()){
        //             send_release_counter++;
        //             if(send_release_counter >= 10){
        //                 break;
        //             }
        //         }
        //     }
        // }
        // }else{
        //     for(uint8_t i = 0; i < 5; i++){
        //         transport_send_release();
        //     }
        // }
        
        sleep_ms(5);
    }
}
