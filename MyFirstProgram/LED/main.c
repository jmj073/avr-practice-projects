/*
 * LED
 *
 * Created: 2022-04-27 22:36:14
 * Author : user
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#define cr_shift(a, n) ((typeof(a)) ((a << (sizeof(a) * 8 - n)) | (a >> n)))
#define cl_shift(a, n) ((typeof(a)) ((a >> (sizeof(a) * 8 - n)) | (a << n)))

//int main()
//{
	//uint8_t right = 0x80, left = 1;
//
	//while (1) {
		//PORTB = right | left;
//
		//right = cr_shift(right, 1);
		//left = cl_shift(left, 1);
	//
		//_delay_ms(500);
	//}
//}

int main() {
	DDRB = 0x01;

	while (1) {
		PORTB ^= 0x01;
		_delay_ms(500);
	}
}

//int main(void)
//{
    //DDRA |= 0x01;
	//
	//while (1) {
		//PORTA |= 0x01;
		//_delay_ms(500);
		//PORTA &= ~0x01;
		//
		//_delay_ms(500);
	//}
//}

