/*
 * digital IO.c
 *
 * Created: 2022-05-05 16:13:31
 * Author : user
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define lshr(a, n) ((typeof(a)) ((a << (sizeof(a) * 8 - n)) | (a >> n)))
#define lshl(a, n) ((typeof(a)) ((a >> (sizeof(a) * 8 - n)) | (a << n)))

#define double_check(s, b, delay) ( \ 
	((s) & (b)) && \ 
	( _delay_ms(delay), ((s) & (b)) )\
 )

void UART0_init();
void UART0_transmit(char data);
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
	UART0_init();
	stdout = &OUTPUT;

    DDRB = 0xFF; // 출력 설정
	DDRA = 0; // 입력 설정
	PORTA = 1; // 풀업 설정
	PORTB = 1;
	
// first solution for de-dounce==============
	//uint8_t cur = 0, prev = 0;
//
	//while (1) {
		//cur = ~PINA;
//
		//if (cur & ~prev & 1) {
			//PORTB = lshl(PORTB, 1);
			//_delay_ms(30);
		//}
	//
		//prev = cur;
	//}
// second solution for de-bounce=============
	uint8_t cur = 0, prev = 0;
	
	while (1) {
		cur = double_check(~PINA, 1, 20);
		
		if (cur & ~prev) {
			PORTB = lshl(PORTB, 1);
			_delay_ms(30);
		}
		
		prev = cur;
	}
}

void UART0_init()
{
	UBRR0H = 0x00;
	UBRR0L = 207;
	
	UCSR0A |= _BV(U2X0);
	UCSR0C |= 0x06;
	
	UCSR0B |= _BV(RXEN0);
	UCSR0B |= _BV(TXEN0);
}

void UART0_transmit(char data)
{
	while ( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = data;
}


//int main()
//{
//DDRB = 0xFF;
//PORTB = 0xFF;
//while (1);
//return 0;
//}