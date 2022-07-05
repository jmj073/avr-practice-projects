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

// ���� ���� PWM ��带 ���� 2���� LED ��� ����==================================

int main() {
	// ���� ��� ���� PB5(OC1A) ��, PB6(OC1B) ���� ������� ����
	DDRB |= nth(PB5) | nth(PB6);
	
	// Ÿ�̸�/ī���� 1���� 8��Ʈ ���� ���� PWM ���� ����
	TCCR1A |= nth(WGM10);
	
	// �� ��ġ A�� ����� ���, �� ��ġ B�� ���� ���� ����
	TCCR1A |= nth(COM1A1);
	TCCR1A |= nth(COM1B1) | nth(COM1B0);
	
	// ���ֺ� 256���� ����
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

//// ��� PWM�� �̿��� LED ��� ����=================================================
//
//int main() {
	//int dim = 0; // ���� LED ���
	//int dir = 1; // ��� ����(1) �Ǵ� ����(-1)
//
	//// ���� ����� OC0(PB4) ���� ���
	//DDRB |= nth(PORTB4);
	//
	//// Ÿ�̸�/ī���� 0���� ��� PWM ���� ����
	//TCCR0 |= nth(WGM01) | nth(WGM00);
	//// ����� ���
	//TCCR0 |= nth(COM01);
	//// ���ֺ� 1,024�� ����
	//TCCR0 |= nth(CS02) | nth(CS01) | nth(CS00);
	//
	//loop {
		//OCR0 = dim; // ��Ƽ ����Ŭ ����
		//_delay_ms(5);
		//
		//dim += dir;
		//if (dim == 0) dir = 1;
		//else if (dim == 255) dir = -1;
	//}
//}