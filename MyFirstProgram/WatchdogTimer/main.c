/*
 * WatchdogTimer.c
 *
 * Created: 2022-06-11 19:22:04
 * Author : user
 */ 

#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <stdio.h>
#include "UART.h"
#include "my_util.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);

//// 워치독 타이머에 의한 리셋==================================================
//int main(void)
//{
	//wdt_enable(WDTO_2S);
	//
	//stdout = &OUTPUT;
	//stdin = &INPUT;
	//
	//UART1_init();
	//
	//printf("Initialization...\r\n");
	//
	//uint16_t count = 0;
	//loop {
		//count++;
		//printf("count: %d\r\n", count);
		//_delay_ms(1000);
	//}
//}

// 워치독 타이머를 리셋=======================================================
int main(void)
{
	wdt_enable(WDTO_2S);
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART1_init();
	
	printf("Initialization...\r\n");
	
	uint16_t count = 0;
	loop {
		count++;
		printf("count: %d\r\n", count);
		_delay_ms(1000);
		
		wdt_reset();
	}
}