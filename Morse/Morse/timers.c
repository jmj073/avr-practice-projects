/*
 * timers.c
 *
 * Created: 2022-06-13 09:27:11
 *  Author: JMJ
 */ 

#include "timers.h"
#include <avr/io.h>

static volatile uint8_t TC1_COMPA_IS_TIMEOVER, TC1_COMPB_IS_TIMEOVER;

void TC1_COMPA_start(uint8_t CS, uint16_t COMP)
{
	TCNT1 = 0;
	OCR1A = COMP;
	TC1_COMPA_IS_TIMEOVER = 0;
	TIFR |= _BV(OCF1A);
	TIMSK |= _BV(OCIE1A);
	TCCR1B |= CS & 0x07;
}

uint8_t TC1_COMPA_stop()
{
	TIMSK &= ~_BV(OCIE1A);
	TCCR1B &= ~0x07;
	
	return TC1_COMPA_IS_TIMEOVER;
}

void TC1_COMPA_timeover()
{
	TIMSK &= ~_BV(OCIE1A);
	TCCR1B &= ~0x07;
	TC1_COMPA_IS_TIMEOVER = 1;
}

void TC1_COMPB_start(uint8_t CS, uint16_t COMP)
{
	TCNT1 = 0;
	OCR1B = COMP;
	TC1_COMPB_IS_TIMEOVER = 0;
	TIFR |= _BV(OCF1B);
	TIMSK |= _BV(OCIE1B);
	TCCR1B |= CS & 0x07;
}

uint8_t TC1_COMPB_stop()
{
	TIMSK &= ~_BV(OCIE1B);
	TCCR1B &= ~0x07;
	
	return TC1_COMPB_IS_TIMEOVER;
}

void TC1_COMPB_timeover()
{
	TIMSK &= ~_BV(OCIE1A);
	TCCR1B &= ~0x07;
	TC1_COMPB_IS_TIMEOVER = 1;
}