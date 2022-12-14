///*
 //* temperature_humidity_sensor.c
 //*
 //* Created: 2022-08-31 11:31:38
 //*  Author: user
 //*/ 
//
//
//#include <avr/io.h>
//#include <util/delay.h>
//#include <stdint.h>
//#include <stdlib.h>
//
//#include "lcd1602_drv.h"
//
//typedef struct __GPIO {
	//volatile uint8_t PIN;		
	//volatile uint8_t DDR;
	//volatile uint8_t PORT;
//} GPIO;
//
//#define GPIOA ((GPIO*)&PINA)
//#define DTH11_GPIO GPIOA
//#define DHT11_PIN 0
//
//static uint8_t c, I_RH, D_RH, I_Temp, D_Temp, CheckSum;
//
//void Request()
//{
	//DTH11_GPIO->DDR |= _BV(DHT11_PIN);
	//DTH11_GPIO->PORT &= ~_BV(DHT11_PIN);
	//_delay_ms(20);
	//DTH11_GPIO->PORT |= _BV(DHT11_PIN);
//}
//
//void Response()
//{
	//DTH11_GPIO->DDR &= ~_BV(DHT11_PIN);
	//
	//while (DTH11_GPIO->PIN & _BV(DHT11_PIN));
	//while ( !(DTH11_GPIO->PIN & _BV(DHT11_PIN)) );
	//while (DTH11_GPIO->PIN & _BV(DHT11_PIN));
//}
//
//uint8_t Receive_data()
//{
	//for (uint8_t q = 0; q < 8; q++) {
		//while ( !(DTH11_GPIO->PIN & _BV(DHT11_PIN)) );
		//_delay_us(30);
		//c = (c << 1) | ((DTH11_GPIO->PIN & _BV(DHT11_PIN)) ? 1 : 0);
		//while (DTH11_GPIO->PIN & _BV(DHT11_PIN));
	//}
	//
	//return c;
//}
//
//int main()
//{
	//char data[5];
	//
	//DDRD = 0x01;
	//
	//lcd_init();
	//
	//while (1) {		
		//Request();
		//Response();
		//PORTD ^= 1;
		//
		//I_RH	= Receive_data(); // 습도 정수부
		//D_RH	= Receive_data(); // 습도 실수부
		//I_Temp	= Receive_data(); // 온도 정수부
		//D_Temp	= Receive_data(); // 온도 실수부
		//CheckSum= Receive_data(); // 체크섬
		//
		//if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum) {
			//lcd_clear();
			//lcd_pos_puts(0, 0, "Error: ");
			//lcd_puts(itoa(CheckSum, data, 10));
		//}
		//else {
			//lcd_pos_puts(0, 0, "H=");
			//lcd_puts(itoa(I_RH, data, 10));
			//lcd_putc('.');
			//lcd_puts(itoa(D_RH, data, 10));
			//lcd_putc('%');
			//
			//
			//
			//lcd_pos_puts(1, 0, "T=");
			//lcd_puts(itoa(I_Temp, data, 10));
			//lcd_putc('.');
			//lcd_puts(itoa(D_Temp, data, 10));
			//lcd_putc(0xDF);
			//lcd_putc('C');
		//}
		//
		//_delay_ms(3000);
	//}
//}