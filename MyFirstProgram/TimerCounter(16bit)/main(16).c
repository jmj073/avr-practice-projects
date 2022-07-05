/*
 * TimerCounter(16bit).c
 *
 * Created: 2022-05-15 16:13:40
 * Author : user
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include <my_util.h>
#include <UART.h>


//// ICP1(PD4) 이벤트 감지=============================================
//// TCCR1B의 ICES1 비트가 0이기 때문에 falling edge를 이벤트로 감지한다
//
//FILE OUTPUT = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
//FILE INPUT = FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);
//
//ISR(TIMER1_CAPT_vect) {
	//uint16_t tcnt1 = TCNT1;
	//uint16_t icr1 = ICR1;
	//
	//printf("input capture:\t%u\r\n", icr1);
	//printf("Timer/Counter:\t%u\r\n", tcnt1);
//}
//
//int main() {
	//PORTD |= nth(4); // 버튼 사용을 위한 내부 풀업 저항 활성화
	//
	//stdout = &OUTPUT;
	//stdin = &INPUT;
	//
	//UART1_init();
	//
	//TCCR1B |= nth(CS12) | nth(CS10); // 분주비 1,024
	//TIMSK |= nth(TICIE1); // 입력 캡쳐 인터럽트 활성화
	//
	//sei();
	//
	//loop;
	//return 0;
//}

//// 비교 일치 인터럽트 파형 출력을 통한 LED 점멸========================================
//
//ISR(TIMER1_COMPA_vect) {
	//TCNT1 = 0;
//}
//
//int main() {
	//// PB5 핀을 출력으로 설정
	//DDRB = 0x20; // OC1A는 PB5이다
	//
	//OCR1A = 0x7FFF; // 비교 일치값 설정
	//TCCR1B |= nth(CS12); // 분주비를 256으로 설정
	//TCCR1A |= nth(COM1A0); // 비교 일치 인터럽트 발생 시 OC1A 핀의 출력을 반전
	//TIMSK |= nth(OCIE1A); // 비교 일치 인터럽트 허용
	//
	//sei();
	//
	//loop;
	//return 0;
//}

//// 비교 일치 A, B, C 인터럽트를 이용한 여러개의 LED 점멸=============================
//
//ISR(TIMER1_COMPA_vect) {
	//PORTB ^= nth(2);
//}
//
//ISR(TIMER1_COMPB_vect) {
	//PORTB ^= nth(2) | nth(1);
//}
//
//ISR(TIMER1_COMPC_vect) {
	//PORTB ^= nth(2) | nth(1) | nth(0);
//}
//
//int main() {
	//DDRB = 0x07;
	//
	//OCR1A = 0x3FFF; // 비교일치 A 1/4초 간격
	//OCR1B = 0x7FFF; // 비교일치 A 2/4초 간격
	//OCR1C = 0xBFFF; // 비교일치 A 3/4초 간격
	//
	//TCCR1B = nth(CS12); // 분주비를 256으로 설정
	//
	//// 비교 일치 A, B, C, 오버플로 인터럽트 활성화
	//TIMSK |= nth(OCIE1A) | nth(OCIE1B) | nth(TOIE1);
	//ETIMSK |= nth(OCIE1C);
	//
	//sei();
	//
	//loop;
	//return 0;
//}

// 비교 일치 A 인터럽트를 이용한 LED 점멸(1번 타이머/카운터)=======================
// 0.5초 간격

ISR(TIMER1_COMPA_vect) {
	PORTB ^= 1;
	TCNT1 = 0;
}

int main(void)
{
	DDRB = 0x01;

	OCR1A |= 0x7FFF; // 비교 일치값 설정
	TCCR1B |= nth(CS12); // 분주비를 256으로 설정
	TIMSK |= nth(OCIE1A); // 비교 일치 A 인터럽트 활성화

	sei();
	
	loop;
	return 0;
}


//// 오버플로 인터럽트를 이용한 LED 점멸(1번 타이머/카운터)==========================
//// 1초 간격
//
//ISR(TIMER1_OVF_vect) {
	//PORTB ^= 1;
//}
//
//int main(void)
//{
    //DDRB = 0x01;
//
	//TCCR1B = nth(CS12); // 분주비를 256으로 설정
	//TIMSK |= nth(TOIE1); // 오버플로 인터럽트 허용
//
	//sei();
	//
	//loop;
	//return 0;
//}
//
