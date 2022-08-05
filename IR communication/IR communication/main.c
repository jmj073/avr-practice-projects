/*
 * IR communication.c
 *
 * Created: 2022-07-24 17:33:25
 * Author : user
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdint.h>
#include "uart.h"

FILE OUTPUT = FDEV_SETUP_STREAM(uart1_putc, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, uart1_getc, _FDEV_SETUP_READ);

static volatile uint16_t bit_cnt = 32;
static volatile uint32_t received_data;

#define NORMAL_LEAD(time) (201 < (time) && (time) < 221)
#define REPEAT_LEAD(time) (166 < (time) && (time) < 186)
#define INVALID_DATA(time) ((time) > 40)
#define TIME_TO_BIT(time) ((time) > 26)

ISR(INT0_vect)
{
	if (TIFR & _BV(TOV0)) { // check overflow
		bit_cnt = 32;
	}
	else {
		uint16_t time = TCNT0;
	
		if (bit_cnt == 32) { // check lead code
			
			if (NORMAL_LEAD(time)) {
				bit_cnt = received_data = 0;
			}
			else if (REPEAT_LEAD(time)) {
				printf("%hu: repeat...\r\n", time);	
			}
			else {
				bit_cnt = 32;
			}
		}
		else {
			if (INVALID_DATA(time)) {
				bit_cnt = 32;
			}
			else {
				received_data = (received_data << 1) | TIME_TO_BIT(time);
			
				if (bit_cnt == 31)
					printf("0x%lX\r\n", received_data);
				
				bit_cnt++;
			}
		}
	}

	TCNT0 = 0;
	TIFR |= _BV(TOV0);
}

int main(void)
{
	uart1_init(UART_BAUD_SELECT(9600, F_CPU));

	stdout = &OUTPUT;
	stdin = &INPUT;
	
	EIMSK |= _BV(INT0);
	EICRA |= _BV(ISC01);
	TCCR0 |= _BV(CS02) | _BV(CS01) | _BV(CS00);
	
	sei();
	
	while (1);
}

