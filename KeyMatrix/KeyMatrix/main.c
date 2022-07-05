/*
 * KeyMatrix.c
 *
 * Created: 2022-05-29 18:42:38
 * Author : user
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <UART.h>
#include <my_util.h>

#define COL_OUT PORTA
#define ROW_IN PINA

FILE OUTPUT = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);

// R4, R3, R2, R1, C1, C2, C3, C4
void read_key(uint8_t key_state[4][4]) 
{
	for (uint8_t col = 0; col < 4; col++) {
		COL_OUT |= 0x0F;
		COL_OUT &= ~(0x01 << (3 - col));
		
		_delay_ms(10);
		
		uint8_t read = ROW_IN >> 4;
		
		for (uint8_t row = 0; row < 4; row++)
			key_state[row][col] = (read >> row) & 1;
	}
}

void print_key(const uint8_t key_state[4][4])
{
	for (uint8_t row = 0; row < 4; row++) {
		for (uint8_t col = 0; col < 4; col++)
			printf("%c ", key_state[row][col] ? '.' : 'O');
		printf("\r\n");
	}
}

int main(void)
{
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART1_init();
	
	DDRA = 0x0F;
	loop {
		uint8_t key_state[4][4];
		read_key(key_state);
		print_key(key_state);
		printf("\r\n\r\n");
		
		_delay_ms(1000);
	}
}

