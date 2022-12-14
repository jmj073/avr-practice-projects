/*
 * ultrasonic.c
 *
 * Created: 2022-11-30 11:37:16
 *  Author: user
 */

// 2.72 = (256 * 1) / F_CPU *  340 / 2 * 1000
// [s] = (256 * 1) / F_CPU
// [m/s] = 340 / 2
// [mm] = 1000

#define CLK_SELECT _BV(CS32) // clk / 256
#define CNT_TO_MM 2.72

#define min(a, b)\
({\
	typeof(a) _a = (a);\
	typeof(b) _b = (b);\
	_a < _b ? _a : _b;\
})

#define max(a, b)\
({\
	typeof(a) _a = (a);\
	typeof(b) _b = (b);\
	_a > _b ? _a : _b;\
})

#include "ultrasonic.h"

#include <avr/interrupt.h>
#include <util/delay.h>

static volatile uint8_t DATA_READY;
static volatile uint16_t DISTANCE; // mm

void ultrasonic_init(void) {
	ULTRASONIC_GPIO->ddr |= _BV(ULTRASONIC_TRIG);
	EICRA |= _BV(ISC01) | _BV(ISC00); // rising edge
	EIFR |= _BV(INTF0);
	EIMSK |= _BV(INT0); // INT0 enable
}

void ultrasonic_trigger(void) {
	ULTRASONIC_GPIO->port |= _BV(ULTRASONIC_TRIG);
	_delay_us(10);
	ULTRASONIC_GPIO->port &= ~_BV(ULTRASONIC_TRIG);

	DATA_READY = 0;
}

uint8_t ultrasonic_data_ready(void) {
	return DATA_READY;
}

uint16_t ultrasonic_get(void) {
	if (DATA_READY) {
		return DISTANCE;
	} else {
		return ULTRASONIC_NOTREADY;	
	}
}


/* external interrupt
 * ISCn1 | ISCn0 | Description
 * ------+-------+------------------------------------------------------------------------
 * 0     | 0     | The low level of INTn generates an interrupt request.
 * 0     | 1     | Reserved.
 * 1     | 0     | The falling edge of INTn generates asynchronously an interrupt request.
 * 1     | 1     | The rising edge of INTn generates asynchronously an interrupt request.
 */
ISR(INT0_vect) {
	//if (DATA_READY) {
		//return;
	//}
	//PORTC |= _BV(0);
	
	uint8_t eicra = EICRA;
	
	if (eicra & _BV(ISC00)) { // rising(펄스 측정 시작)
		TCNT3 = 0;
		TCCR3B |= CLK_SELECT;
	} else { // falling(펄스 측정 끝)
		TCCR3B &= ~0x07; // clk_src disable
		
		if (ETIFR & _BV(TOV3)) {
			ETIFR |= _BV(TOV3);
			
			DISTANCE = ULTRASONIC_MAX_DISTANCE;
		} else {
			uint16_t cnt = TCNT3;
			cnt = min(cnt, (uint16_t)(ULTRASONIC_MAX_DISTANCE / CNT_TO_MM));
			DISTANCE = cnt * CNT_TO_MM;
		}
		
		DATA_READY = 1;
	}
	
	EICRA = eicra ^ _BV(ISC00);
	EIFR |= _BV(INTF0);
}