/*
 * ShiftRegister.c
 *
 * Created: 2022-05-24 23:32:51
 * Author : user
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <my_util.h>
#include <UART.h>
#include <stdio.h>

#define set_bit(n) (PORTB |= nth(n))
#define clear_bit(n) (PORTB &= ~nth(n))

#define SHIFT_CLOCK 0
#define LATCH_CLOCK 1
#define DATA		2

typedef uint8_t u8;

void shift_clock()
{
	set_bit(SHIFT_CLOCK);
	//_delay_us(1);
	clear_bit(SHIFT_CLOCK);
}

void latch_clock()
{
	set_bit(LATCH_CLOCK);
	//_delay_us(1);
	clear_bit(LATCH_CLOCK);
}

void shift_out(u8 data) 
{
	for (u8 i = 0; i < 8; i++) {
		if (data & 0x80)
			set_bit(DATA);
		else
			clear_bit(DATA);
			
			shift_clock();
			data <<= 1;
	}
	
	latch_clock();
}

// FND 숫자 출력=======================================================

static const u8 digits[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x6F };

int main() {
	DDRB |= nth(SHIFT_CLOCK) | nth(LATCH_CLOCK) | nth(DATA);
	
	u8 digit = 0;
	loop {
		shift_out(~digits[digit]);
		digit = (digit + 1) % 10;
		_delay_ms(500);
	}
}

//// LED 회전 회오리===================================================
//int main()
//{
	//DDRB |= nth(SHIFT_CLOCK) | nth(LATCH_CLOCK) | nth(DATA);
	//
	//uint8_t out = 0x01;
	//loop {
		//shift_out(out = lrs(out, 1));
		//_delay_ms(500);
	//}
//}