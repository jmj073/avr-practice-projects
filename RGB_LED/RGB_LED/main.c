/*
 * RGB_LED.c
 *
 * Created: 2022-10-26 09:37:34
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define R OCR1AL
#define G OCR1BL
#define B OCR1CL

static void timer_init() {
	TCCR1A |= (
		_BV(WGM10)		| // mode1: PWM, Phase Correct, 8-bit
		_BV(COM1A1) 	| 
		_BV(COM1B1) 	| 
		_BV(COM1C1) 	| 
	0);
	
	
}

int main(void)
{
	timer_init();

    TCCR1B |= _BV(CS12); // clk_io/256

	DDRB |= 0xE0;

	for (uint8_t v = 0; v < 256; v++) {
		R = v;
		G = 255 - v;
		B = 128 - v;
		_delay_ms(10);
	}

	//while (1) {
		//R = 255;
		//_delay_ms(500);
		//R = 0;
		//
		//G = 255;
		//_delay_ms(500);
		//G = 0;
		//
		//B = 255;
		//_delay_ms(500);
		//B = 0;
	//}
}

