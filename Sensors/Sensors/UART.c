/*
 * UART.c
 *
 * Created: 2022-05-05 21:29:55
 *  Author: JMJ
 */ 

#include <avr/io.h>

// UART0============================================================

void UART0_init()
{
	UBRR0H = 0x00; // 9,600 ������ ����
	UBRR0L = 207;
	
	UCSR0A |= _BV(U2X0); // 2��� ���
	// �񵿱�, 8��Ʈ ������, �и�Ƽ ����, 1��Ʈ ���� ��Ʈ ���
	UCSR0C |= 0x06;
	
	// �ۼ��� ����
	UCSR0B |= _BV(RXEN0); 
	UCSR0B |= _BV(TXEN0);
}

void UART0_transmit(char data)
{
	while ( !(UCSR0A & (1 << UDRE0)) ); // �۽� ���� ���
	UDR0 = data; // ������ ����
}

unsigned char UART0_receive()
{
	while ( !(UCSR0A & (1 << RXC0)) ); // ������ ���� ���
	return UDR0;
}

// UART1============================================================

void UART1_init()
{
	UBRR1H = 0x00; // 9,600 ������ ����
	UBRR1L = 207;
	
	UCSR1A |= _BV(U2X1); // 2��� ���
	// �񵿱�, 8��Ʈ ������, �и�Ƽ ����, 1��Ʈ ���� ��Ʈ ���
	UCSR1C |= 0x06;
	
	// �ۼ��� ����
	UCSR1B |= _BV(RXEN1);
	UCSR1B |= _BV(TXEN1);
}

void UART1_transmit(char data)
{
	while ( !(UCSR1A & (1 << UDRE1)) ); // �۽� ���� ���
	UDR1 = data; // ������ ����
}

unsigned char UART1_receive()
{
	while ( !(UCSR1A & (1 << RXC1)) ); // ������ ���� ���
	return UDR1;
}
