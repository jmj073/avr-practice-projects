/*
 * FND
 *
 * Created: 2022-05-10 09:07:20
 * Author : JMJ
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#define double_check(s, b, delay) ( \
((s) & (b)) && \
( _delay_ms(delay), ((s) & (b)) )\
)

#define nb(n) (1 << n)

#define DOT_POINT 0x80

// ==================================================================================

typedef uint8_t u8;

const u8 digits[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x6F };
	
const u8 ascii[] = { 
	['H'] = 0x76, ['E'] = 0x79, ['L'] = 0x38, 
	['O'] = 0x3F, ['i'] = 0x30, ['t'] = 0x78, 
	['s'] = 0x6D, ['d'] = 0x5E, ['a'] = 0x5F,
	['e'] = 0x7B, ['o'] = 0x5C, ['g'] = 0x6F,
};

// ==================================================================================
	
static inline void fnd4_num(volatile u8* dst, volatile u8* nth, int src) {
	
	for (u8 i = nb(3); i; i >>= 1) {
		*nth = (*nth & ~0x0F) | i;
		*dst = ~digits[src % 10];
		src /= 10;
		_delay_ms(2);
	}
}
static inline void fnd4_str(volatile u8* dst, volatile u8* nth, const char* src) {
	
	for (u8 i = 1; i != nb(4); i <<= 1) {
		*nth = (*nth & ~0x0F) | i;
		*dst = ~ascii[*src++];
		_delay_ms(2);
	}
}
	
// ==================================================================================
	
int main()
{
	DDRB = 0xFF; // O fnd
	DDRA |= 0x0F; // O unit
	
	DDRC &= ~0x03; // I button
	PORTC |= 0x3; // built-in pullup
	
	const char* o = "HELLO it is daedeog HELL";
	const char* cur = o;
	
	uint8_t delta = 0;
	while (1) {
		u8 in = ~PINC;
		delta = (delta & ~((in >> 1) ^ in) | ~(in >> 1) & in) & 1;
		cur += delta;
		
		if (!cur[4]) cur = o;
		
		for (int i = 0; i < 125; i++)
			fnd4_str(&PORTB, &PORTA, cur);
	}
}	
	
//int main(void)
//{
	//DDRB = 0xFF; // O fnd 
	//DDRA |= 0x0F; // O digit
	//
	//DDRC &= ~0x0F; // I button
	//PORTC |= 0xF; // built-in pullup
	//
	//int delta = 0, num = 0;
	//while (1) {
		//u8 in = ~PINC;
		//if (in & nb(0))
			//delta = 1;			
		//else if (in & nb(1))
			//delta = -1;
		//else if (in & nb(2))
			//delta = 0;
		//else if (in & nb(3))
			//num = 0;
			//
		//num += delta;
		//if (num < 0 || num >= 10000)
			//delta = 0, num = 0;
		//
		//for (int i = 0; i < 50; i++)
			//fnd4_num(&PORTB, &PORTA, num);
	//}
//}

//int main() {
	//DDRB = 0xFF;
	//DDRA = 0x0F;
	//
	//// u8 nums[4] = {0,};
	//
	//u8 digit = 1;
	//while (1) {
		//for (int i = 0; i < 10; i++) {
			//PORTA = digit;
			//PORTB = ~digits[i];
			//digit <<= 1;
			//if (digit == 0x10) digit = 1;
			//_delay_ms(500);
		//}
	//}
//}

