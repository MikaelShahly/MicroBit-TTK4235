#include "uart.h"

void uart_init() {
    GPIO0->PIN_CNF[6] = 0;
    GPIO1->PIN_CNF[8] = 1;
    UART->PSEL_TXD = 0;
    UART->PSEL_RXD = 0;                          //unsure if c sign extends binary numbers 
    UART->PSEL_TXD |= (1<<3) | (1<<5); //Configur TXD pin
    UART->PSEL_RXD |= (1<<1) | (1<<2);
    UART->BAUDRATE = 0x00275000;
    UART->PSEL_CTS = (1<<31);
    UART->PSEL_RTS = (1<<31);
    UART->ENABLE |= 4;
    UART->TASKS_STARTRX |= 1;
}


void uart_send(char letter) {
    UART->TASKS_STARTTX |= 1;
    UART->TXD |= (uint32_t) letter;
    while(!UART->EVENTS_TXDRDY) {

    }
    UART->TASKS_STOPTX |= 1;
}

char uart_read() {
    UART->TASKS_STARTRX |= 1;

    if(!UART->EVENTS_RXDRDY) {
        UART->TASKS_STOPRX |=1;
        return '\0';
    }

    UART->EVENTS_RXDRDY = 0;
    char val = (char) UART->RXD;
    UART->TASKS_STOPRX |= 1;
    return val;
}