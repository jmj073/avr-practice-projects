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
	UBRR0H = 0x00; // 9,600 보율로 설정
	UBRR0L = 207;
	
	UCSR0A |= _BV(U2X0); // 2배속 모드
	// 비동기, 8비트 데이터, 패리티 없음, 1비트 정지 비트 모드
	UCSR0C |= 0x06;
	
	// 송수신 가능
	UCSR0B |= _BV(RXEN0); 
	UCSR0B |= _BV(TXEN0);
}

void UART0_transmit(char data)
{
	while ( !(UCSR0A & (1 << UDRE0)) ); // 송신 가능 대기
	UDR0 = data; // 데이터 전송
}

unsigned char UART0_receive()
{
	while ( !(UCSR0A & (1 << RXC0)) ); // 데이터 수신 대기
	return UDR0;
}

// UART1============================================================

void UART1_init()
{
	UBRR1H = 0x00; // 9,600 보율로 설정
	UBRR1L = 207;
	
	UCSR1A |= _BV(U2X1); // 2배속 모드
	// 비동기, 8비트 데이터, 패리티 없음, 1비트 정지 비트 모드
	UCSR1C |= 0x06;
	
	// 송수신 가능
	UCSR1B |= _BV(RXEN1);
	UCSR1B |= _BV(TXEN1);
}

void UART1_transmit(char data)
{
	while ( !(UCSR1A & (1 << UDRE1)) ); // 송신 가능 대기
	UDR1 = data; // 데이터 전송
}

unsigned char UART1_receive()
{
	while ( !(UCSR1A & (1 << RXC1)) ); // 데이터 수신 대기
	return UDR1;
}
