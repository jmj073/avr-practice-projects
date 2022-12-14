/*
 * IR.c
 *
 * Created: 2022-11-16 09:49:46
 *  Author: user
 */ 

#include <avr/io.h>

#define LASER	0
#define IR		1

int main() {
	DDRA |= _BV(LASER);
	
	while (1) {
		if (PINA & _BV(IR)) {
			PORTA |= _BV(LASER);
		} else {
			PORTA &= ~_BV(LASER);
		}
	}
}