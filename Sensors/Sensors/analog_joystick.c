/*
 * analog_joystick.c
 *
 * Created: 2022-10-19 10:06:57
 *  Author: user
 */ 

//#include <avr/io.h>
//#include <util/delay.h>
//#include <stdio.h>
//#include "ADC.h"
//#include "lcd1602_drv.h"
//
//void ADC_Init()
//{
	//DDRF = 0x00;
	//ADCSRA = 0x87;
	//ADMUX = 0x40;
//}
//int ADC_Read(char channel)
//{
	//int ADC_value;
	//
	//ADMUX = (0x40) | (channel & 0x07);
	//_delay_us(50);
	//ADCSRA |= (1<<ADSC);
	//while((ADCSRA &(1<<ADIF))== 0);
	//
	//ADCSRA |= (1<<ADIF);
	//return ADCW;
//}
//
//
//int main(void)
//{
	//char buffer[32];
	//int ADC_Value;
	//
	//ADC_Init();
	//lcd_init();
	//
	//PORTF |= _BV(2);
	//
	//while(1)
	//{
		//ADC_Value = ADC_Read(0);
		//sprintf(buffer, "X= %4d", ADC_Value);
		//lcd_pos_puts(0, 0, buffer);
		//
		//ADC_Value = ADC_Read(1);
		//sprintf(buffer, " Y= %4d", ADC_Value);
		//lcd_puts(buffer);
		//
		//if(PINF & _BV(2)) {
			//lcd_pos_puts(1, 0, "Switch open   ");
		//} else {
			//lcd_pos_puts(1, 0, "Switch pressed");
		//}
		//
		//_delay_ms(500);
	//}
//}
