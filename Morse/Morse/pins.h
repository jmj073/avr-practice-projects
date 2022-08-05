/*
 * pins.h
 *
 * Created: 2022-06-14 09:47:23
 *  Author: user
 */ 

/*
+ 추가로 봐야할 파일들:
	+ lcd1602_drv.h
*/

#ifndef PINS_H_
#define PINS_H_

#include <avr/io.h>
#include "my_util.h"

/* SEt Bit */
#define _SEB(x, pin, bit) ((void)(x(pin) |= _BV(bit)))
/* CLear Bit */
#define _CLB(x, pin, bit) ((void)(x(pin) &= ~_BV(bit)))


#define LED_PIN (&PINB)
#define LED_BIT 0
#define LED_seb(X) _SEB(X, LED_PIN, LED_BIT)
#define LED_clb(X) _CLB(X, LED_PIN, LED_BIT)
#define LED_ON() LED_seb(PORT)
#define LED_OFF() LED_clb(PORT)

#define BUTTON_PIN (&PINB)
#define BUTTON_BIT 1
#define BUTTON_seb(X) _SEB(X, BUTTON_PIN, BUTTON_BIT)
#define BUTTON_clb(X) _CLB(X, BUTTON_PIN, BUTTON_BIT)
#define BUTTON_PRESSED() (~PIN(BUTTON_PIN) & _BV(BUTTON_BIT))


#endif /* PINS_H_ */