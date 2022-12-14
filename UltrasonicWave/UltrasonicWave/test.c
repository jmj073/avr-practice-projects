/*
 * test.c
 *
 * Created: 2022-09-14 10:46:16
 *  Author: user
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define TRIG 6
#define ECHO 7
#define SOUND_VELOCITY 340UL

typedef struct
{
	volatile uint8_t pin;
	volatile uint8_t ddr;
	volatile uint8_t port;
} GPIO;

#define UMW_GPIO ((GPIO*)&PIND)

int main(void)
{	
	unsigned int distance;
	unsigned int i;
	DDRB = 0x10;
	DDRD |= 0x01;
	UMW_GPIO->ddr = ((UMW_GPIO->ddr | (1<<TRIG)) & ~(1<<ECHO));
	
	while(1)
	{
		TCCR1B = 0x03;
		UMW_GPIO->port &= ~(1<<TRIG);
		_delay_us(10);
		UMW_GPIO->port |= (1<<TRIG);
		_delay_us(10);
		UMW_GPIO->port &= ~(1<<TRIG);
		while ( !(UMW_GPIO->pin & (1<<ECHO)) );
		TCNT1 = 0x0000;
		while (UMW_GPIO->pin & (1<<ECHO));
		TCCR1B = 0x00;
		distance = (unsigned int)(SOUND_VELOCITY * (TCNT1 * 4 / 2) / 1000);

		//음파의?속도는?340m/s?이므로?1cm를?이동하는데?약?29us. 왕복거리
		
		if(distance < 100){
			for(i=0; i<5; i++)
			{
				PORTB = 0x10;
				_delay_ms(1);
				PORTB = 0x00;
				_delay_ms(1);
			}
		} else if(distance < 200){
			for(i=0; i<5; i++)
			{
				PORTB = 0x10;
				_delay_ms(1);
				PORTB = 0x00;
				_delay_ms(1);
			}
			_delay_ms(100);
		}   else if(distance < 500){
			for(i=0; i<5; i++)
			{
				PORTB = 0x10;
				_delay_ms(1);
				PORTB = 0x00;
				_delay_ms(1);
			}
			_delay_ms(300);
		}
	}
}