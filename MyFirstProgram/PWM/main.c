/*
 * PWM.c
 *
 * Created: 2022-05-15 23:19:28
 * Author : JMJ
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#include <my_util.h>

// 위상 교정 PWM 모드를 통한 2개의 LED 밝기 제어==================================

int main() {
	// 파형 출력 핀인 PB5(OC1A) 핀, PB6(OC1B) 핀을 출력으로 설정
	DDRB |= nth(PB5) | nth(PB6);
	
	// 타이머/카운터 1번을 8비트 위상 교정 PWM 모드로 설정
	TCCR1A |= nth(WGM10);
	
	// 비교 일치 A는 비반전 모드, 비교 일치 B는 반전 모드로 설정
	TCCR1A |= nth(COM1A1);
	TCCR1A |= nth(COM1B1) | nth(COM1B0);
	
	// 분주비를 256으로 설정
	TCCR1B |= nth(CS12);
	
	int dim = 0;
	int dir = 1;
	
	loop {
		OCR1A = dim;
		OCR1B = dim;
		
		_delay_ms(10);
		
		dim += dir;
		
		if (dim == 0) dir = 1;
		else if (dim == 255) dir = -1;
	}
}

//// 고속 PWM을 이용한 LED 밝기 제어=================================================
//
//int main() {
	//int dim = 0; // 현재 LED 밝기
	//int dir = 1; // 밝기 증가(1) 또는 감소(-1)
//
	//// 파형 출력핀 OC0(PB4) 핀을 출려
	//DDRB |= nth(PORTB4);
	//
	//// 타이머/카운터 0번을 고속 PWM 모드로 설정
	//TCCR0 |= nth(WGM01) | nth(WGM00);
	//// 비반전 모드
	//TCCR0 |= nth(COM01);
	//// 분주비를 1,024로 설정
	//TCCR0 |= nth(CS02) | nth(CS01) | nth(CS00);
	//
	//loop {
		//OCR0 = dim; // 듀티 사이클 설정
		//_delay_ms(5);
		//
		//dim += dir;
		//if (dim == 0) dir = 1;
		//else if (dim == 255) dir = -1;
	//}
//}