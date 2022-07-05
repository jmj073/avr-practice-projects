/*
 * Sensors.c
 *
 * Created: 2022-06-11 20:56:49
 * Author : user
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "ADC.h"
#include "UART.h"
#include "my_util.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);
 
 
// 온도 센서(LM35)================================================================

//int main(void)
//{
	//stdout = &OUTPUT;
	//stdin = &INPUT;
	//
	//ADC_init(3);
	//UART1_init();
	    //
	//loop {
		//int read = read_ADC();
		//printf("%d\r\n", (int)(read * 5.0 / 1023.0 * 100.0));
		//_delay_ms(1000);
	//}
//}

// 조도 센서(Cds)=================================================================

//int main(void)
//{
	//stdout = &OUTPUT;
	//stdin = &INPUT;
	//
	//ADC_init(5);
	//UART1_init();
	//
	//loop {
		//printf("%d\r\n", read_ADC());
		//_delay_ms(1000);
	//}
//}

// 초음파 거리 센서===============================================================

int main()
{
	
}