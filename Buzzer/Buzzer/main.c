/*
 * Buzzer.c
 *
 * Created: 2022-07-24 21:37:44
 * Author : user
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

enum Notes {
	B3	= 246,
	
	C4	= 261,
	Cs4	= 277,
	D4	= 293,
	Ds4	= 311,
	E4	= 329,
	F4	= 349,
	Fs4	= 369,
	G4	= 392,
	Gs4 = 415,
	A4	= 440,
	As4 = 466,
	B4	= 493,
	
	C5	= 523,
	Cs5 = 554,
	D5	= 587,
	Ds5	= 622,
	E5	= 659,
	F5	= 698,
	Fs5	= 739,
	G5	= 784,
	Gs5	= 830,
	A5	= 880,
	As5	= 932,
	B5	= 987,
};

#define PAUSE 0
#define NONE 1
#define PRESCALER 8

#define NOTE 0
#define RHYTHM 1

/* /16 */
#define UNIT (170 * 16)


// C D F G => sharp
static const uint16_t melody[][2] = {
	{Gs4, 8},	{E4, 16},
	{NONE, 16},	{NONE, 16},
	{E4, 16},	{Gs4, 8},
	{Fs4, 8},	{B3, 16}, 
	{NONE, 16},	{NONE, 16},	{NONE, 16},
	{Fs4, 16},	{Gs4, 16}, 
		
	{A4, 16},	{NONE, 16},
	{Fs4, 16},	{NONE, 16},
	{Fs4, 16},	{NONE, 16},
	{A4, 16},	{Gs4, 16},	{NONE, 16},
	{E4, 16},	{NONE, 16},	{NONE, 8},
	{NONE, 16},	{E4, 8},

	{Cs5, 8},	{NONE, 8},
	{B4, 8},	{A4, 16},	{B4, 16},
	{B4, 8},	{Gs4, 8},	{Fs4, 8},	{E4, 8},

	{Fs4, 1},

	{NONE, 4},	{E5, 16},	{E5, 16},	{E5, 16},	{E5, 16},
	{Ds5, 8},	{B4, 8},
	{Ds5, 8},	{E5, 16},	{Cs5, 16},

	{Cs5, 16},	{Cs5, 16},	{Cs5, 16},
	{A4, 16},	{A4, 16},	{A4, 16},
		
	
	
		
	{PAUSE, 0},
};

static const uint16_t melody2[][2] = {
	{C4, 1}, {C4, 1}, {C4, 1}, {C4, 1}, {PAUSE, 0},
};

static void init_delay()
{
	TCCR3B |= _BV(WGM12);
}

void delay(uint16_t ms) {

	OCR3A = F_CPU / 1000 / 1024 * ms;
	TCCR3B |= 0x05;
	
	while ( !(ETIFR & _BV(OCF3A)) );
	ETIFR |= _BV(OCF3A);
	TCCR3B &= 0x07;
	TCNT3 = 0;
}

static void init_music()
{
	DDRB |= _BV(PB6);
	TCCR1A |= _BV(COM1B0); // 비교 일치시에 출력 반전
	TCCR1B |= _BV(WGM12) | _BV(CS11); // 4번 CTC 모드, 분주비 8
	
	TCCR3B |= _BV(WGM12);
	ETIMSK |= _BV(OCIE3A);
}

static void play_music(const uint16_t (*melody)[2])
{
	while ((*melody)[NOTE] != PAUSE) {
		if ((*melody)[NOTE] == NONE) {
			OCR1A = 0; TCNT3 = 0;
		}
		else {
			OCR1A = F_CPU / 2 / PRESCALER / (*melody)[NOTE];
			TCNT3 = 0;
		}
		delay(UNIT / (*melody)[RHYTHM]);
		melody++;
	}
	
	OCR1A = 0;
	TCNT3 = 0;
}

int main(void)
{
	PORTA = 0x01;
	
	init_music();
	init_delay();
	
	while (PINA & 0x01);
	
	while (1) {
		play_music(melody);
		_delay_ms(1000);
	}
}

//int main(void)
//{
	////init_music();
	//init_delay();
	//
	//DDRD = 0x01;
	//
	//while (1) {
		//PORTD ^= 0x01;
		//delay(340);
	//}
//}