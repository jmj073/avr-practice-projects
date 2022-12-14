/*
 * Bluetooth.c
 *
 * Created: 2022-07-23 18:03:30
 * Author : JMJ
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>
#include "uart.h"

#define UART_BAUD_RATE0 38400
#define UART_BAUD_RATE1 9600

int main(void)
{
    uart0_init(UART_BAUD_SELECT(UART_BAUD_RATE0, F_CPU)); // bluetooth
	uart1_init(UART_BAUD_SELECT(UART_BAUD_RATE1, F_CPU)); // computer
	
	sei();
	
	uart1_puts("hello, world!\r\n");
	
	while (1) {
		uint16_t c;
		
		c = uart0_getc();
		if (!(c & UART_NO_DATA)) {
			if (c & 0xFF00) {
				uart1_puts("error from 0(bluetooth)\n\r");
			} else {
				uart1_putc((uint8_t)c);
			}
		}
		
		c = uart1_getc();
		if (!(c & UART_NO_DATA)) {
			if (c & 0xFF00) {
				uart1_puts("error from 1(computer)\n\r");
			} else {
				uart0_putc((uint8_t)c);
				//uart1_puts("put to? bluetooth!\n\r");
			}
		}
	}
}
