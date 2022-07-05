/*
 * TimerCounter.c
 *
 * Created: 2022-05-14 16:57:30
 * Author : user
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <my_util.h>

// 실행 시간을 통한 LED 점멸==========================================================


volatile uint32_t timer0_millis;
volatile uint16_t timer0_micros;

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

int main() {
	TIMER0_init();
	
	DDRB = 0x01;
	
	uint32_t prev = 0, cur;

	uint8_t state = 0x00;
	PORTB = state;	
	
	sei();
	loop {
		cur = millis();
		
		if (cur - prev > 1000) { // 1초 경과
			prev = cur;
			state ^= 1;
			PORTB = state;
		}
	}
	
	return 0;
}

//// 외부 오실레이터를 통한 LED 점멸====================================================
//
//ISR(TIMER0_COMP_vect) {
	//PORTB ^= 0x01;
	//uint32_t a;
//}
//
//int main() {
	//DDRB = 0x01;
	//
	//ASSR |= nth(AS0); // 외부 오실레이터 사용 설정
	//
	//// 분주비를 128로 설정. 32.768KHz 오실레이터를 사용시 오버플로 인터럽트가 1s마다 일어나게 된다
	//TCCR0 |= nth(CS02) | nth(CS00);
	//
	//TIMSK |= nth(TOIE0); // 오버플로 인터럽트 허용
	//
	//sei();
	//loop;
	//
	//return 0;
//}

//// 비교 일치 인터럽트와 OCn핀 파형 출력을 이용한 LED 점멸=============================
//
//int count;
//
//ISR(TIMER0_COMP_vect)
//{
	//count++;
	//TCNT0 = 0;
//}
//
//int main() {
	//DDRB = 0x10; // 파형 출력 핀인 OC(PB4) 핀을 출력으로 설정
	//PORTB = 0x00;
	//
	//// 분주비 설정: 1,024
	//TCCR0 |= nth(CS02) | nth(CS01) | nth(CS00);
//
	//OCR0 = 255; // 비교 일치 기준값
	//TCCR0 |= nth(COM00); // 비교 일치 인터럽트 발생 시 OC0 핀의 출력을 반전
	//TIMSK |= nth(OCIE0); // 비교 일치 인터럽트 허용
	//
	//sei();
	//loop;
	//
	//return 0;
//}

//// 비교 일치 인터럽트를 이용한 LED 점멸=============================================
//
//int count;
//
//ISR(TIMER0_COMP_vect)
//{
	//count++;
	////TCNT0 = 0; // CTC모드를 사용하지 않을 시에는 0으로 만들 필요가 있음
	//
	//if (count == 64) {
		//count = 0;
		//PORTB ^= 1;
	//}
//}
//
//int main() {
	//DDRB = 0x01;
	//PORTB = 0x00;
	//
	//// 분주비 설정: 1,024, CTC 모드
	//TCCR0 |= nth(CS02) | nth(CS01) | nth(CS00) | nth(WGM01); 
//
	//OCR0 = 128; // 비교 일치 기준값
	//TIMSK |= nth(OCIE0); // 비교 일치 인터럽트 허용
	//
	//sei();
	//loop;
	//
	//return 0;
//}


//// 오버플로 인터럽트를 이용한 LED 점멸==============================================
//
//int count;
//
//ISR(TIMER0_OVF_vect) {
	//count++;
	//
	//if (count == 32) {
		//count = 0;
		//PORTB ^= 1;
	//}
//}
//
//int main(void)
//{
    //DDRB = 0x01;
	//PORTB = 0x00;
	//
	//TCCR0 |= nth(CS02) | nth(CS01) | nth(CS00); // 분주비 설정
	//
	//TIMSK |= nth(TOIE0); // 오버플로 인터럽트 허용
	//
	//sei();
	//
	//loop;
	//return 0;
//}

