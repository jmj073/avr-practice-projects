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



//// �Ƴ��α� �Է��� ���� LED ���� �ֱ� ����===================================
//
///*
	//16M�� 16MHz�� �ý��� Ŭ�Ͽ��� ���� ��
	//
	//1 = (1 / 16M) * (���ֺ� * ����ġ)
	//���ֺ� * �� ��ġ = 16M
//
	//16M = 16 * 1000 * 1000
	//���� �Ʒ��� ���
	//2^4 * 2^10 * 2^10 = 2^24
//
	//����ġ�� �ִ� 2^16 -1 �̱� ������ 
	//���ֺ� >= (2^24) / (2^16 - 1) = 2^8 ����
//
	//���ֺ� 256���� �ϸ�
	//�� ��ġ = 16M / 256 = 62500
//*/
//#define MAX_PERIOD 62500
//
//ISR(ADC_vect) { // ADC ��ȯ �Ϸ� ISR
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
	//// Ÿ�̸�/ī����	
	//TCCR1B |= nth(WGM12); // CTC ���
	//TCCR1B |= nth(CS12); // ���ֺ� 256���� ����
	//
	//OCR1A = MAX_PERIOD; // �� ��ġ�� ����. 1��
	//TIMSK |= nth(OCIE1A); // �� ��ġ A ���ͷ�Ʈ Ȱ��ȭ
	//
	//// ADC
	//ADCSRA |= nth(ADIE); // ADC ��ȯ �Ϸ�� ���ͷ�Ʈ Ȱ��ȭ
	//ADC_init(0); // ADC0(PF0)���� �Ƴ��α� �Է� ����
	//
	//sei();
	//
	//loop;
	//return 0;
//}

