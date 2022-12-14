/*
 * ultrasonic.h
 *
 * Created: 2022-11-30 11:37:02
 *  Author: user
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "avr_gpio.h"

#define ULTRASONIC_GPIO GPIOD
#define ULTRASONIC_TRIG	1

#define ULTRASONIC_MAX_DISTANCE 5000
#define ULTRASONIC_NOTREADY ((uint16_t)-1)

void ultrasonic_init(void);
void ultrasonic_trigger(void);

uint8_t ultrasonic_data_ready(void);
uint16_t ultrasonic_get(void);

#endif /* ULTRASONIC_H_ */