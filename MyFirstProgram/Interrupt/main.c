/*
 * Interrupt
 *
 * Created: 2022-05-11 15:06:41
 * Author : JMJ
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include <UART.h>
#include <my_util.h>

// ���ͷ�Ʈ�� ���� LED ����3================================================

//FILE OUTPUT = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
//FILE INPUT = FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);

volatile uint8_t flag;

ISR(INT0_vect) {
	flag ^= 1;
}

int main() {
	//stdout = &OUTPUT;
	//stdin = &INPUT;
	//UART1_init();
	
	DDRB = 0xFF; // OUTPUT: LEDs
	PORTD = 0x01; // pull-up
	
	EIMSK |= nth(INT0); // enable INT0 & INT1
	// fall(������)
	EICRA |= nth(ISC01);
	sei();
	
	PORTB = 0x01;
	
	loop {
		PORTB = flag ? rrs(PORTB, 1) : lrs(PORTB, 1);
		_delay_ms(500);
	}
}

//// ���ͷ�Ʈ�� ���� LED ����2================================================
//
//FILE OUTPUT = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
//FILE INPUT = FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);
//
//ISR(INT0_vect) {
	//PORTB = 0x00;
	//printf("INT0 occurred!\r\n");
//}
//
//ISR(INT1_vect) {
	//PORTB = 0xFF;
	//printf("INT1 occurred!\r\n");
//}
//
//int main() {
	//stdout = &OUTPUT;
	//stdin = &INPUT;
	//UART1_init();
	//
	//DDRB = 0xFF; // OUTPUT: LEDs
	//PORTD = 0x03; // pull-up
	//
	//EIMSK |= nth(INT0) | nth(INT1); // enable INT0 & INT1
	//
	//// �� fall(������) | �� rise(����)
	//EICRA |= nth(ISC01) | nth(ISC10); 
	//
	//sei();
	//
	//loop;
//}

//// ���ͷ�Ʈ�� ���� LED ����1================================================
//
//volatile uint8_t state; // LED state
//
//ISR(INT0_vect) {
	//state ^= 1;
//}
//
//void INIT_PORT() {
	//DDRB = 0x01; // OUTPUT: LED
	//DDRD = 0x00; // INTPUT: BUTTON
	//PORTD = 0x01; // built-in pull-up resistance
//}
//
//void INIT_INT0() {
	//EIMSK |= nth(INT0);		// INT0 ���ͷ�Ʈ Ȱ��ȭ
	//EICRA |= nth(ISC01);	// �ϰ� edge���� ���ͷ�Ʈ �߻�
	//sei();					// ���������� ���ͷ�Ʈ ���
//}
//
//
//int main(void)
//{
	//INIT_PORT();
	//INIT_INT0();
	//
	//loop PORTB = state;
	//
	//return 0;
//}