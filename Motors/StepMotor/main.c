/*
 * StepMotor.c
 *
 * Created: 2022-06-09 21:34:32
 * Author : JMJ
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <my_util.h>


#define step_forward(step) (step = (step + 1) % 4, 1 << step)
#define step_backward(step) (step = (step + 3) % 4, 1 << step)

// forward: 시계
// backward: 반시계


 1상 여자 방식
int main() {
	DDRC = 0x0F;
	PORTC = 0x0F;
	uint8_t s = 0;
	
	//loop {
		//PORTC = step_forward(s);
		//_delay_ms(2);
	//}
	
	loop {
		for (int i = 0; i < 2037; i++) {
			PORTC = step_forward(s);
			_delay_ms(2);
		}
		
		_delay_ms(1000);
		
		for (int i = 0; i < 2037; i++) {
			PORTC = step_backward(s);
			_delay_ms(2);
		}
		
		_delay_ms(1000);
	}
	
	//loop {
		//PORTC = nth(2);
		//_delay_ms(5);
		//PORTC = nth(0);
		//_delay_ms(5);
	//}	
	
	//loop {
		//PORTC = nth(3);
		//_delay_ms(5);
		//PORTC = nth(2);
		//_delay_ms(5);
		//PORTC = nth(1);
		//_delay_ms(5);
		//PORTC = nth(0);
		//_delay_ms(5);
	//}
	
	//for (int i = 0; i < 2037; i++) {
		//PORTC = step_forward(s);
		//_delay_ms(2);
	//}
	
	loop;
}


// 74595(SIPO Resgister)를 사용하여 제어========================================

#define LATCH_CLK nth(PORTC0)
#define SHIFT_CLK nth(PORTC1)
#define DATA nth(PORTC2)

inline void shift_clock() {
	PORTC |= SHIFT_CLK;
	PORTC &= ~SHIFT_CLK;
}

inline void latch_clock() {
	PORTC |= LATCH_CLK;
	PORTC &= ~LATCH_CLK;
}

int main() {
	DDRC = 0x07;

	uint8_t period = 7;
	loop {
		if (++period == 8) {
			period = 0;
			PORTC |= DATA;
		}
		else 
			PORTC &= ~DATA;
			
		_delay_ms(5);
			
		shift_clock();
		latch_clock();
	}
}