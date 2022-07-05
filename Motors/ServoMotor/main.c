/*
 * ServoMotor.c
 *
 * Created: 2022-06-07 23:39:52
 * Author : JMJ
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <my_util.h>

#define ROTATION_DELAY	2000 // 1�� ���
#define PULSE_MIN		1300 // �ּ� �޽� ����
#define PULSE_MID		3000
#define PULSE_MAX		4700 // �ִ� �޽� ����

void Timer1_init()
{
	// ��� 14. ��� PWM ���
	// TOP: ICR1
	TCCR1A |= nth(WGM11);
	TCCR1B |= nth(WGM12) | nth(WGM13);
	
	// ����� ���
	TCCR1A |= nth(COM1A1);
	
	TCCR1B |= nth(CS11); // ������ 8, 2MHz
	
	ICR1 = 39999; // 20ms �ֱ�
}

int main()
{
	DDRB |= nth(5);
	
	loop {
		PORTB = nth(5);
		_delay_ms(2);
		PORTB = 0;
		
		_delay_ms(30);
	}
}

//int main(void)
//{
    //DDRB |= nth(PORTB5); // OC1A
	//
	//Timer1_init();
	//
	//loop {
		//OCR1A = PULSE_MIN;
		//_delay_ms(ROTATION_DELAY);
		//
		//OCR1A = PULSE_MID;
		//_delay_ms(ROTATION_DELAY);
		//
		//OCR1A = PULSE_MAX;
		//_delay_ms(ROTATION_DELAY);
	//}
	//
	//return 0;
//}

