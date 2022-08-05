/*
 * Buzzer.c
 *
 * Created: 2022-07-24 21:37:44
 * Author : user
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define C4 262
#define D4 294
#define E4 330
#define F4 349
#define G4 392
#define A4 440
#define B4 494
#define C5 523
#define PAUSE 0
#define PRESCALER 8

static const uint16_t melody[] = {
	C4, D4, E4, G4, A4, B4, C5, PAUSE,
};

static void init_music()
{
	DDRB |= _BV(PB6);
	TCCR1A |= _BV(COM1B0); // 비교 일치시에 출력 반전
	TCCR1B |= _BV(WGM12) | _BV(CS11); // 4번 CTC 모드, 분주비 8
}

static void play_music(const uint16_t* notes)
{
	while (*notes != PAUSE) {
		OCR1A = F_CPU / 2 / PRESCALER / *notes++;
		_delay_ms(500);
	}
	
	OCR1A = 0;
}

int main(void)
{
	init_music();
	
	while (1) {
		play_music(melody);
		_delay_ms(1000);
	}
}

