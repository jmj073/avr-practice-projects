/*
 * button.h
 *
 * Created: 2022-12-14 10:05:05
 *  Author: user
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "avr_gpio.h"

#define BTN_GPIO GPIOB
#define BTN_PIN	0

static inline
void btn_init(void) {
	BTN_GPIO->ddr &= ~_BV(BTN_PIN);
}

static inline
uint8_t btn_pressed() {
	return !(BTN_GPIO->pin >> BTN_PIN);
}

#endif /* BUTTON_H_ */