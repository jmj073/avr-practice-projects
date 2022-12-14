///*
 //* UltrasonicWave.c
 //*
 //* Created: 2022-09-14 09:49:28
 //* Author : user
 //*/ 
//
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <stdint.h>
//
//typedef struct 
//{
	//volatile uint8_t pin;	
	//volatile uint8_t ddr;
	//volatile uint8_t port;
//} GPIO;
//
//#define GPIOD ((GPIO*)&PIND)
//
//#define INT0_GPIO	GPIOD
//#define int0_PIN	0
//
//static void init_buzzer()
//{
	//DDRB |= _BV(PB6);
	//TCCR1A |= _BV(COM1B0); // 비교 일치시에 출력 반전
	//TCCR1B |= _BV(WGM12) | _BV(CS11); // 4번 CTC 모드, 분주비 8
//}
//
//void Qpush(uint16_t ms)
//{
	//uint16_t dist = ms * 17; // mm
	//
	//OCR1A = F_CPU / 2 / 8 / dist;
//}
//
//void start_timer()
//{
	//uint8_t tccr1b = TCCR1B &= ~0x07;
//
	//TCNT1 = 0;
	//TIFR |= _BV(TOV1); // clear flag
	 //
	//TCCR1B |= tccr1b | _BV(CS12) | _BV(CS10); // 1024 prescale
//}
//
//uint16_t stop_timer()
//{
	//TCCR1B &= ~0x07;
	//
	//if (TIFR & _BV(TOV1)) {
		//TIFR |= _BV(TOV1); // clear flag
		//return -1;
	//}
	//
	//return TCNT1 * 1024 / (F_CPU / 1000);
//}
//
//ISR(INT0_vect)
//{
	//uint8_t eicra = EICRA ^= _BV(ISC00);
	//
	//if (eicra & _BV(ISC00)) { // if falling edge
		//Qpush(stop_timer());
	//}
	//else { // if rising edge
		//start_timer();
	//}
//}
//
//int main(void)
//{	
	//init_buzzer();
	//
	//EICRA |= _BV(ISC01) | _BV(ISC00); // rising edge
	//EIFR = _BV(INTF0);
	//EIMSK |= _BV(INT0);
	//
	//sei();
	//
	//while (1) {
		//
	//}
//}
//
