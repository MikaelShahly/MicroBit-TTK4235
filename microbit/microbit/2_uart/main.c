#include "uart.h"

#define GPIO0_LEDS_ON (0X01688000)

int main(){
    gpio_init();
    uart_init();

    while(1){
        if(!(GPIO0->IN & (1<<14))) {
            uart_send('A');
        }
        if(!(GPIO0->IN & (1<<23))) {
            uart_send('B');
        }

        //implement logic turning on/off led matrix when letters recieved
        if(uart_read() != '\0') {
            uint32_t LED_val_GPIO0 = GPIO0->IN & (1<<11) & (1<<19) & (1<<21) & (1<<22) & (1<<24) & (1<<28) & (1<<30) & (1<<31);
            uint32_t LED_val_GPIO1 = GPIO1->IN & (1<<5);

            if(LED_val_GPIO0 == GPIO0_LEDS_ON && LED_val_GPIO1 == 0) {
                gpio_lights_off();
            } else {
                gpio_lights_on();
            }
        }
    }

    return 0;
}