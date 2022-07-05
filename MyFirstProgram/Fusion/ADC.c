#include <avr/io.h>
#include <my_util.h>

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