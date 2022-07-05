#include <avr/io.h>
#include <my_util.h>

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