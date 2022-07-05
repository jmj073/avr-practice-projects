/*
 * uart0.c
 *
 * Created: 2021-04-06 오후 2:48:18
 *  Author: kccistc
 */ 
#include "uart0.h"

char rxBuff[100] = {0,};
uint8_t rxFlag = 0;

void UART0_ISR_Process(void)
{
	static uint8_t tail = 0;
	uint8_t rxData = UDR0;
	
	if(rxData == ';')
	{
		rxBuff[tail] = '\0';
		tail = 0;
		rxFlag = 1;
	}
	else
	{
		rxBuff[tail] = rxData;
		tail++;
	}
}

void UART0_Init(void)
{
	UBRR0H=0x00;   //대부분 0
	UBRR0L=16;      //데이터 통신 속도를 의미한다. 115200 baudrate
	UCSR0A|=(1<<U2X0);
	
	UCSR0B|=(1<<RXEN0)|(1<<TXEN0);//Rx enable/ Tx enable
	
	UCSR0B|=(1<<RXCIE0);// 수신 Rx UART0 인터럽트 Enabale
}

void UART0_Transmit(unsigned int data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char UART0_Receive(void)
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}

void UART0_print_string(char *str)
{
	for(int i=0;str[i];i++)
	{
		UART0_Transmit(str[i]);
	}
}