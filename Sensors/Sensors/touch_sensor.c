/*
 * touch_sensor.c
 *
 * Created: 2022-11-02 09:11:55
 *  Author: user
 */ 

#include <avr/io.h>
#include <util/delay.h>

struct gpio {
	volatile uint8_t PIN;
	volatile uint8_t DDR;
	volatile uint8_t PORT;
};

#define PORT_RGB ((struct gpio*)&PINB)
#define RGB_R	4
#define RGB_G	5
#define RGB_B	6
#define R	_BV(RGB_R)
#define G	_BV(RGB_G)
#define B	_BV(RGB_B)
#define RGB (R | G | B)

#define PORT_TOUCH	((struct gpio*)&PINA)
#define TOUCH_PIN 0

static const uint8_t colors[] = {
	R, G, B, R | B
};

//int main() {
	//
	//PORT_RGB->DDR |= RGB;
	//PORT_TOUCH->DDR &= ~_BV(TOUCH_PIN);
	//
	//while (!(PORT_TOUCH->PIN & _BV(TOUCH_PIN)));
	//
	//uint8_t prev = 0, idx = 0;
	//
	//while (1) {
		//uint8_t curr = PORT_TOUCH->PIN & _BV(TOUCH_PIN);
		//if (~prev & curr) {
			//PORT_RGB->PORT = (PORT_RGB->PORT & ~(RGB)) | colors[idx];
			//idx = (idx + 1) & 3;
		//}
		//prev = curr;
		////_delay_ms(15);
	//}
//}

//int main() {
//
	//PORT_RGB->DDR |= RGB;
	//PORT_TOUCH->DDR &= ~_BV(TOUCH_PIN);
//
	//while (1) {
		//if (PORT_TOUCH->PIN & _BV(TOUCH_PIN)) {
			//PORT_RGB->PORT |= R;
		//} else {
			//PORT_RGB->PORT &= ~R;
			////_delay_ms(500);
		//}
	//}
//}

//int main() {
//
	//PORT_TOUCH->DDR |= _BV(TOUCH_PIN);
//
	//while (1) {
		//PORT_TOUCH->PORT ^= _BV(TOUCH_PIN);
		//_delay_ms(500);
	//}
//}