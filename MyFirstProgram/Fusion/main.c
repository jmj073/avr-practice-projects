/*
 * fusion
 *
 * Created: 2022-05-15 20:59:42
 * Author : JMJ
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <my_util.h>

#include <ADC.h>



//// 아날로그 입력을 통한 LED 점멸 주기 제어===================================
//
///*
	//16M는 16MHz의 시스템 클록에서 나온 수
	//
	//1 = (1 / 16M) * (분주비 * 비교일치)
	//분주비 * 비교 일치 = 16M
//
	//16M = 16 * 1000 * 1000
	//위는 아래와 비슷
	//2^4 * 2^10 * 2^10 = 2^24
//
	//비교일치는 최대 2^16 -1 이기 때문에 
	//분주비 >= (2^24) / (2^16 - 1) = 2^8 정도
//
	//분주비를 256으로 하면
	//비교 일치 = 16M / 256 = 62500
//*/
//#define MAX_PERIOD 62500
//
//ISR(ADC_vect) { // ADC 변환 완료 ISR
	//uint16_t tmp = (ADC / 1023.0) * MAX_PERIOD;
	//
	//if (tmp < MAX_PERIOD / 10)
		//tmp = MAX_PERIOD / 10;
	//
	//OCR1A = tmp;
//}
//
//ISR(TIMER1_COMPA_vect) {
	//PORTB = lrs(PORTB, 1);
//}
//
//int main(void)
//{
    //DDRB = 0xFF; // OUTPUT: LED
	//PORTB = 0x01;
	//
	//// 타이머/카운터	
	//TCCR1B |= nth(WGM12); // CTC 모드
	//TCCR1B |= nth(CS12); // 분주비를 256으로 설정
	//
	//OCR1A = MAX_PERIOD; // 비교 일치값 설정. 1초
	//TIMSK |= nth(OCIE1A); // 비교 일치 A 인터럽트 활성화
	//
	//// ADC
	//ADCSRA |= nth(ADIE); // ADC 변환 완료시 인터럽트 활성화
	//ADC_init(0); // ADC0(PF0)에서 아날로그 입력 받음
	//
	//sei();
	//
	//loop;
	//return 0;
//}

