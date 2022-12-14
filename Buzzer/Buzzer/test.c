/*
 * test.c
 *
 * Created: 2022-09-21 12:09:00
 *  Author: user
 */ 


//#include <avr/io.h>
//#include <util/delay.h>
//
//unsigned char count;
//unsigned int data=0;
//
//static void init_delay()
//{
//TCCR3B |= _BV(WGM12);
//}
//
//void delay(unsigned long us) {
//
	//OCR3A = F_CPU / 1000000 / 1024 * us;
	//TCCR3B |= 0x05;
//
	//while ( !(ETIFR & _BV(OCF3A)) );
	//ETIFR |= _BV(OCF3A);
	//TCCR3B &= 0x07;
	//TCNT3 = 0;
//}
//
//
//void buzzer(unsigned long hz, unsigned long rhythm){
	//
	//hz = 1000000 / hz;
	//rhythm = (170 * 16) / hz / rhythm;
	//for (uint16_t i = 0; i < rhythm; i++) {
		//PORTB ^= 1 << 6;
		//delay(hz);
	//}
//}
//
//
//int main() {
//
	//init_delay();
//
	//int i;
	//DDRB = 1 << 6;
//
	//while(1) {
//
		//for(i=0;i<20;i++) {
			//buzzer(261,8);
			//buzzer(277,8);
			//buzzer(329,8);
			//buzzer(349,8);
			//buzzer(391,8);
			//buzzer(440,8);
			//buzzer(493,8);
			//buzzer(523,8);
//
		//}
		//_delay_ms(2000);
//
	//}
//
	//return 0;
//
//}