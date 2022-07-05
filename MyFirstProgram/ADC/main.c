/*
 * ADC.c
 *
 * Created: 2022-05-08 14:06:57
 * Author : user
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <UART.h>

#define nth(n) (1 << n)
#define loop for (;;)

FILE OUTPUT = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);

void ADC_init(uint8_t channel)
{
	ADMUX |= nth(REFS0); // AVCC�� ���� �������� ����
	
	ADCSRA |= 0x07; // ���ֺ� ����
	ADCSRA |= nth(ADEN); // ADC Ȱ��ȭ
	ADCSRA |= nth(ADFR); // �������� ���
	
	ADMUX = ((ADMUX & 0xE0) | channel); // ä�� ����
	
	ADCSRA |= nth(ADSC); // ��ȯ ����
}

int read_ADC()
{
	while ( !(ADCSRA & nth(ADIF)) ); // ��ȯ ���
	return ADC;
}

void Comparator_init()
{
	 ACSR |= nth(ACBG); // ���� ��尸 ���� ���
}

// f������ �Ƴ��α� �񱳱� ����ϱ�
int main() {
	stdout = &OUTPUT;
	stdin = &INPUT;
	UART1_init();
	
	DDRB |= 0x01;
	
	ACSR |= nth(ACBG); // ���� �Է����� ���� bandgap ���� ���
	SFIOR |= nth(ACME); // ���� �Է����� �Ƴ��α� �Է��� ���
	ADMUX &= ~0x07; // ���� �Է����� 0�� �� ���
	
	loop {
		PORTB = (PORTB & ~0x01) | ((ACSR >> ACO) & 1);
		printf("%s\r\n", (ACSR & nth(ACO)) ? "BIG: >" : "<=");
		_delay_ms(1000);
	}
}

//// ������ ���鼭 Ȯ��
//int main()
//{
	//stdout = &OUTPUT;
	//stdin = &INPUT;
	//
	//UART1_init();
	//ADC_init(0);
	//
	//loop {
		//ADCSRA |= nth(ADSC);
		//int f00 = read_ADC();
		//_delay_ms(500);
		//ADCSRA |= nth(ADSC);
		//int f01 = read_ADC();
		//ADMUX ^= 0x01;
		//
		//ADCSRA |= nth(ADSC);
		//int f10 = read_ADC();
		////_delay_ms(500);
		//ADCSRA |= nth(ADSC);
		//int f11 = read_ADC();
		//ADMUX ^= 0x01;
		//
		//printf("(%d, %d, %d, %d)%X\r\n", f00, f01, f10, f11, ADCSRA);
		////printf("%d\r\n", f00);
	//}
//}

 //�Ƴ��α� �񱳱�
//int main()
//{
	//stdout = &OUTPUT;
	//stdin = &INPUT;
	//
	//UART1_init();
	//ADC_init(0);
	//Comparator_init();
	//
	//DDRB |= 0x01;
	//
	//loop {
		//float voltage = read_ADC() * 5.0 / 1024;
		//PORTB = (PORTB & ~0x01) | ((ACSR >> ACO) & 0x01);
		//
		//printf("Voltage: %f, \tLED is %s!!\r\n", voltage, PORTB & 1 ? "ON" : "OFF");
		//
		//_delay_ms(1000);
	//}
//}

//// bandgap ������ �̿��� AVCC ���
//int main()
//{
	//stdout = &OUTPUT;
	//stdin = &INPUT;
	//
	//UART1_init();
	//ADC_init(0b11110);
	//
	//loop {
		//printf("AVCC = %f\r\n", (1.23 * 1023) / read_ADC());
		//_delay_ms(1000);
	//}
//}

//// �Ƴ��α� �Է°��� �̿��� LED ����
//int main(void)
//{
	//DDRB = 0xFF;
//
	//stdout = &OUTPUT;
	//stdin = &INPUT;
//
	//UART1_init();
	//ADC_init(0);
//
	//loop {
		//PORTB = (uint8_t)~0 >> ((read_ADC() >> 7) - 1);		
		//_delay_ms(1000);
	//}
//
	//return 0;
//}

//// �Ƴ��α� �Է°� ���
//int main(void)
//{	
	//stdout = &OUTPUT;
	//stdin = &INPUT;
	//
	//UART1_init();
	//ADC_init(0);
	//
	//loop {
		//printf("%d\r\n", read_ADC());
		//_delay_ms(1000);
	//}
	//
	//return 0;
//}