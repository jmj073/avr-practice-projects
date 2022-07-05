/*
 * I2C_LCD.c
 *
 * Created: 2021-04-07 오전 11:25:36
 * Author : kccistc
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart0.h"
#include "I2C.h"
#include "i2c_lcd.h"


//FILE OUTPUT = FDEV_SETUP_STREAM(UART0_Transmit, NULL, _FDEV_SETUP_WRITE);

int main(void)
{	
	LCDInit();
	//UART0_Init();
	//stdout =&OUTPUT;
	
	LCDWriteStringXY(0,0,"hello world");
	int c=0;
	char stbuf[30];
    while (1) 
    {
		sprintf(stbuf,"count :%d",c++);
		LCDWriteStringXY(1,0,stbuf);
		_delay_ms(500);
    }
}

