/*
 * switch.c
 *
 * Created: 2022-04-12 08:30:51
 * Author : user
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define DOT_POINT 0x80

typedef uint8_t u8;

const u8 digits[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x6F };

int main() {
	DDRB = 0xFF;
	DDRA = 0x0F;
	
	// u8 nums[4] = {0,};
	
	u8 digit = 1;
	while (1) {		
		for (int i = 0; i < 10; i++) {
			PORTA = digit;
			PORTB = ~digits[i];
			digit <<= 1;
			if (digit == 0x10) digit = 1;
			_delay_ms(500);
		}
	}
}

// double switch
// int main() {
// 	DDRB = 0xFF;
// 	DDRA = 0x00;
//
// 	while (1) {
// 		u8 in = ~PINA;
// 		u8 out = 0;
//
// 		if (in & 1)
// 		out |= 0x55;
//
// 		if (in & 2)
// 		out |= 0xAA;
//
// 		PORTB = out;
// 	}
//}

// ½ºÀ§Ä¡
// int main() {
// 	DDRB = 0xFF;
// 	DDRA = 0x00;
//
// 	while (1) {
// 		PORTB = (PINA & 1 ? 0x00 : 0xFF);
// 	}
//}
