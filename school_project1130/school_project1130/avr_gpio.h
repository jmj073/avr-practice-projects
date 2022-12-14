/*
 * avr_gpio.h
 *
 * Created: 2022-11-30 11:31:50
 *  Author: user
 */ 


#ifndef AVR_GPIO_H_
#define AVR_GPIO_H_

#include <stdint.h>
#include <avr/io.h>

struct avr_gpio {
	volatile uint8_t pin;
	volatile uint8_t ddr;
	volatile uint8_t port;
};

#define GPIOA ((struct avr_gpio*)(&PINA))
#define GPIOB ((struct avr_gpio*)(&PINB))
#define GPIOC ((struct avr_gpio*)(&PINC))
#define GPIOD ((struct avr_gpio*)(&PIND))
#define GPIOE ((struct avr_gpio*)(&PINE))


#endif /* AVR_GPIO_H_ */