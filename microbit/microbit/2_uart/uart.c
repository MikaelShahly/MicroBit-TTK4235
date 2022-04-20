#include "uart.h"
#include "gpio.h"

void uart_init() {
    GPIO0->PIN_CNF[6] = 0;
    GPIO1->PIN_CNF[8] = 1;
    UART->PSEL_RXD |= (1<<1) || (1<<2);
    UART->PSEL_TXD |= (1<<3) || (1<<5); //må aktivere port 1 pga init txd pin er på GPIO1
    UART->PSEL_TXD = 0; //bit extender alt til å være 0
    UART->PSEL_RXD = 0;
    UART->BAUDRATE = 0x00275000;        //BRUKER IKKE BITWISE PGA VI IKKE ER INTRESSERT I Å BEHOLDE/ISOLERE NOEN BITS
    UART->PSEL.CTS = (1<<31);
    UART->PSEL.RTS = (1<<31);
    UART->ENABLE |= 4;
    UART->TASKS_STARTRX |= 1;
}

void uart_send(char letter) {
    UART->STARTTX |= 0x1;
    UART->TXD = (uint32_t )letter;
    while (UART->EVENTS_TXDRDY != 0x1) {

    }
    UART->TASKS_STOPRX |= 0x1;      //kunne nok og brukt 1 istedefor 0x1  
}

char uart_read() {
    UART->TASKS_STARTRX |= 1;

}