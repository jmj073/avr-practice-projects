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
	ADMUX |= nth(REFS0); // AVCC를 기준 전압으로 선택
	
	ADCSRA |= 0x07; // 분주비 설정
	ADCSRA |= nth(ADEN); // ADC 활성화
	ADCSRA |= nth(ADFR); // 프리러닝 모드
	
	ADMUX = ((ADMUX & 0xE0) | channel); // 채널 선택
	
	ADCSRA |= nth(ADSC); // 변환 시작
}

int read_ADC()
{
	while ( !(ADCSRA & nth(ADIF)) ); // 변환 대기
	return ADC;
}

void Comparator_init()
{
	 ACSR |= nth(ACBG); // 내부 밴드갭 전압 사용
}

// f핀으로 아날로그 비교기 사용하기
int main() {
	stdout = &OUTPUT;
	stdin = &INPUT;
	UART1_init();
	
	DDRB |= 0x01;
	
	ACSR |= nth(ACBG); // 양의 입력으로 내부 bandgap 전압 사용
	SFIOR |= nth(ACME); // 음의 입력으로 아날로그 입력핀 사용
	ADMUX &= ~0x07; // 음의 입력으로 0번 핀 사용
	
	loop {
		PORTB = (PORTB & ~0x01) | ((ACSR >> ACO) & 1);
		printf("%s\r\n", (ACSR & nth(ACO)) ? "BIG: >" : "<=");
		_delay_ms(1000);
	}
}

//// 번갈아 가면서 확인
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

 //아날로그 비교기
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

//// bandgap 전압을 이용한 AVCC 계산
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

//// 아날로그 입력값을 이용한 LED 제어
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

//// 아날로그 입력값 출력
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