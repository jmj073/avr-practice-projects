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


//// ICP1(PD4) �̺�Ʈ ����=============================================
//// TCCR1B�� ICES1 ��Ʈ�� 0�̱� ������ falling edge�� �̺�Ʈ�� �����Ѵ�
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
	//PORTD |= nth(4); // ��ư ����� ���� ���� Ǯ�� ���� Ȱ��ȭ
	//
	//stdout = &OUTPUT;
	//stdin = &INPUT;
	//
	//UART1_init();
	//
	//TCCR1B |= nth(CS12) | nth(CS10); // ���ֺ� 1,024
	//TIMSK |= nth(TICIE1); // �Է� ĸ�� ���ͷ�Ʈ Ȱ��ȭ
	//
	//sei();
	//
	//loop;
	//return 0;
//}

//// �� ��ġ ���ͷ�Ʈ ���� ����� ���� LED ����========================================
//
//ISR(TIMER1_COMPA_vect) {
	//TCNT1 = 0;
//}
//
//int main() {
	//// PB5 ���� ������� ����
	//DDRB = 0x20; // OC1A�� PB5�̴�
	//
	//OCR1A = 0x7FFF; // �� ��ġ�� ����
	//TCCR1B |= nth(CS12); // ���ֺ� 256���� ����
	//TCCR1A |= nth(COM1A0); // �� ��ġ ���ͷ�Ʈ �߻� �� OC1A ���� ����� ����
	//TIMSK |= nth(OCIE1A); // �� ��ġ ���ͷ�Ʈ ���
	//
	//sei();
	//
	//loop;
	//return 0;
//}

//// �� ��ġ A, B, C ���ͷ�Ʈ�� �̿��� �������� LED ����=============================
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
	//OCR1A = 0x3FFF; // ����ġ A 1/4�� ����
	//OCR1B = 0x7FFF; // ����ġ A 2/4�� ����
	//OCR1C = 0xBFFF; // ����ġ A 3/4�� ����
	//
	//TCCR1B = nth(CS12); // ���ֺ� 256���� ����
	//
	//// �� ��ġ A, B, C, �����÷� ���ͷ�Ʈ Ȱ��ȭ
	//TIMSK |= nth(OCIE1A) | nth(OCIE1B) | nth(TOIE1);
	//ETIMSK |= nth(OCIE1C);
	//
	//sei();
	//
	//loop;
	//return 0;
//}

// �� ��ġ A ���ͷ�Ʈ�� �̿��� LED ����(1�� Ÿ�̸�/ī����)=======================
// 0.5�� ����

ISR(TIMER1_COMPA_vect) {
	PORTB ^= 1;
	TCNT1 = 0;
}

int main(void)
{
	DDRB = 0x01;

	OCR1A |= 0x7FFF; // �� ��ġ�� ����
	TCCR1B |= nth(CS12); // ���ֺ� 256���� ����
	TIMSK |= nth(OCIE1A); // �� ��ġ A ���ͷ�Ʈ Ȱ��ȭ

	sei();
	
	loop;
	return 0;
}


//// �����÷� ���ͷ�Ʈ�� �̿��� LED ����(1�� Ÿ�̸�/ī����)==========================
//// 1�� ����
//
//ISR(TIMER1_OVF_vect) {
	//PORTB ^= 1;
//}
//
//int main(void)
//{
    //DDRB = 0x01;
//
	//TCCR1B = nth(CS12); // ���ֺ� 256���� ����
	//TIMSK |= nth(TOIE1); // �����÷� ���ͷ�Ʈ ���
//
	//sei();
	//
	//loop;
	//return 0;
//}
//
