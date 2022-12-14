/*
 * DCMotor.c
 *
 * Created: 2022-08-31 09:48:09
 * Author : user
 */ 


#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

typedef struct __GPIO{
	volatile uint8_t PIN;	
	volatile uint8_t DDR;
	volatile uint8_t PORT;
} GPIO;


#define GPIOA ((GPIO*)&PINA)

#define MOTOR_GPIO	GPIOA
#define M0	0
#define M1	1

static void Port_Init()
{
	GPIOA->DDR = 0xFF;
}

int main(void)
{
	Port_Init();
	
	while (1) {
		MOTOR_GPIO->PORT = _BV(M0) | _BV(M1);
		_delay_ms(1000);
		MOTOR_GPIO->PORT = _BV(M1);
		_delay_ms(1000);
		MOTOR_GPIO->PORT = _BV(M0) | _BV(M1);
		_delay_ms(1000);
		MOTOR_GPIO->PORT = _BV(M0);
		_delay_ms(1000);
	}
}

