/*
 * TimerCounter.c
 *
 * Created: 2022-05-14 16:57:30
 * Author : user
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <my_util.h>

// ���� �ð��� ���� LED ����==========================================================


volatile uint32_t timer0_millis;
volatile uint16_t timer0_micros;

// ATmega128�� 16MHz�� �ý��� Ŭ���� ����ϹǷ�
// 64�� ���ֺ� ����ϸ� 64 * 256 / 16M = 1.024ms���� 
// �����÷� ���ͷ�Ʈ�� �߻��Ѵ�.

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

// ����ð��� �����ϱ� ���� ����� �� �ִ�.
uint32_t millis() {
	uint8_t oldSREG = SREG;
	cli();
	
	uint32_t m = timer0_millis;
	
	SREG = oldSREG;
	return m;
}

void TIMER0_init() {
	TCCR0 |= nth(CS02); // ���ֺ� 64 ����
	TIMSK |= nth(TOIE0); // �����÷� ���ͷ�Ʈ ���
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
		
		if (cur - prev > 1000) { // 1�� ���
			prev = cur;
			state ^= 1;
			PORTB = state;
		}
	}
	
	return 0;
}

//// �ܺ� ���Ƿ����͸� ���� LED ����====================================================
//
//ISR(TIMER0_COMP_vect) {
	//PORTB ^= 0x01;
	//uint32_t a;
//}
//
//int main() {
	//DDRB = 0x01;
	//
	//ASSR |= nth(AS0); // �ܺ� ���Ƿ����� ��� ����
	//
	//// ���ֺ� 128�� ����. 32.768KHz ���Ƿ����͸� ���� �����÷� ���ͷ�Ʈ�� 1s���� �Ͼ�� �ȴ�
	//TCCR0 |= nth(CS02) | nth(CS00);
	//
	//TIMSK |= nth(TOIE0); // �����÷� ���ͷ�Ʈ ���
	//
	//sei();
	//loop;
	//
	//return 0;
//}

//// �� ��ġ ���ͷ�Ʈ�� OCn�� ���� ����� �̿��� LED ����=============================
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
	//DDRB = 0x10; // ���� ��� ���� OC(PB4) ���� ������� ����
	//PORTB = 0x00;
	//
	//// ���ֺ� ����: 1,024
	//TCCR0 |= nth(CS02) | nth(CS01) | nth(CS00);
//
	//OCR0 = 255; // �� ��ġ ���ذ�
	//TCCR0 |= nth(COM00); // �� ��ġ ���ͷ�Ʈ �߻� �� OC0 ���� ����� ����
	//TIMSK |= nth(OCIE0); // �� ��ġ ���ͷ�Ʈ ���
	//
	//sei();
	//loop;
	//
	//return 0;
//}

//// �� ��ġ ���ͷ�Ʈ�� �̿��� LED ����=============================================
//
//int count;
//
//ISR(TIMER0_COMP_vect)
//{
	//count++;
	////TCNT0 = 0; // CTC��带 ������� ���� �ÿ��� 0���� ���� �ʿ䰡 ����
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
	//// ���ֺ� ����: 1,024, CTC ���
	//TCCR0 |= nth(CS02) | nth(CS01) | nth(CS00) | nth(WGM01); 
//
	//OCR0 = 128; // �� ��ġ ���ذ�
	//TIMSK |= nth(OCIE0); // �� ��ġ ���ͷ�Ʈ ���
	//
	//sei();
	//loop;
	//
	//return 0;
//}


//// �����÷� ���ͷ�Ʈ�� �̿��� LED ����==============================================
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
	//TCCR0 |= nth(CS02) | nth(CS01) | nth(CS00); // ���ֺ� ����
	//
	//TIMSK |= nth(TOIE0); // �����÷� ���ͷ�Ʈ ���
	//
	//sei();
	//
	//loop;
	//return 0;
//}

