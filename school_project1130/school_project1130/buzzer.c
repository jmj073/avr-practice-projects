/*
 * buzzer.c
 *
 * Created: 2022-11-30 10:14:21
 *  Author: user
 */ 

#include "buzzer.h"

#include <avr/io.h>

static uint16_t FREQ;

#define CLK_SELECT _BV(CS12)

void buzzer_init(void) {
	DDRB |=	_BV(PORTB5); // OC1A
	
	TCCR1A |= (
		_BV(WGM11) | _BV(WGM10)		| // FastPWM(15)
		_BV(COM1A0)					| // OCnA toggle
	0);
	
	TCCR1B |= _BV(WGM13) | _BV(WGM12); // FastPWM(15)
}

void buzzer_set_freq(uint16_t freq) {
	if (freq) {
		//OCR1A = (F_CPU / (2 * 256) + (freq >> 1)) / freq - 1;
		OCR1A = (F_CPU / (2 * 256)) / freq - 1;
		TCCR1B |= CLK_SELECT; // clk / 256	
	} else {
		TCCR1B &= ~0x07; // clk_src disable
		TCNT1 = 0;
	}
	
	FREQ = freq;
}

uint16_t buzzer_get_freq(void) {
	return FREQ;
}