/*
 * EEPROM.c
 *
 * Created: 2022-06-11 14:34:36
 * Author : JMJ
 */ 

#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include <my_util.h>
#include <UART.h>

FILE OUTPUT = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);


// latency 측정========================================================

static volatile uint32_t timer0_millis;
static volatile uint16_t timer0_micros;

// ATmega128은 16MHz의 시스템 클록을 사용하므로
// 64의 분주비를 사용하면 64 * 256 / 16M = 1.024ms마다
// 오버플로 인터럽트가 발생한다.

ISR(TIMER0_OVF_vect) {
	uint32_t m = timer0_millis;
	uint16_t f = timer0_micros;
	
	m += 1;
	f += 24;
	
	m += f / 1000;
	f %= 1000;
	
	timer0_millis = m;
	timer0_micros = f;
}

// 실행시간을 측정하기 위해 사용할 수 있다.
uint32_t millis() {
	uint8_t oldSREG = SREG;
	cli();
	
	uint32_t m = timer0_millis;
	
	SREG = oldSREG;
	return m;
}

void TIMER0_init() {
	TCCR0 |= nth(CS02); // 분주비 64 설정
	TIMSK |= nth(TOIE0); // 오버플로 인터럽트 허용
}

#define COUNT 10

int main()
{
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	TIMER0_init();
	UART1_init();
	
	sei();
	
	uint32_t prev, cur;
	
	printf("** Start Writing...\r\n");
	prev = millis();
	for (int i = 0; i < COUNT; i++)
		eeprom_write_byte((uint8_t*)i, i);
	cur = millis();
	printf("Write to EEPROM takes %ld ms, %lu\r\n", cur - prev, cur);
	
	printf("** Start Reading...\r\n");
	prev = millis();
	for (int i = 0; i < COUNT; i++)
		eeprom_read_byte((uint8_t*)i);
	cur = millis();
	printf("Read from takes %ld ms, %lu\r\n", cur - prev, cur);
	
	loop;
}

// R/W test============================================================
//int main(void)
//{
    //stdout = &OUTPUT;
	//stdin = &INPUT;
	//
	//UART1_init();
	//
	//eeprom_update_block("are you okay?", 1 << 12, 13);
	//
	//char buf[14] = { 0 };
	//eeprom_read_block(buf, 0, 13);
	//printf("%s\r\n", buf);
	//
	//loop;
//}