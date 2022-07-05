#include <avr/io.h>
#include <my_util.h>
#include "../include/I2C.h"
// #include <I2C.h>

void I2C_init()
{
	DDRD |= nth(I2C_SCL) | nth(I2C_SDA);
	
	TWBR = 32; // 클록 주파수 설정 200KHz
}

void I2C_start()
{
	TWCR = nth(TWINT) | nth(TWSTA) | nth(TWEN);
	
	while( !(TWCR & nth(TWINT)) ); // 시작 완료 대기
}

void I2C_transmit(uint8_t data)
{
	TWDR = data;
	
	TWCR = nth(TWINT) | nth(TWEN) | nth(TWEA);
	while ( !(TWCR & nth(TWINT)) ); // 전송 완료 대기
}

uint8_t I2C_receive_ACK()
{
	TWCR = nth(TWINT) | nth(TWEN) | nth(TWEA);
	while ( !(TWCR & nth(TWINT)) ); // 수신 완료 대기

	return TWDR;
}

uint8_t I2C_receive_NACK()
{
	TWCR = nth(TWINT) | nth(TWEN);
	while ( !(TWCR & nth(TWINT)) ); // 수신 완료 대기
	
	return TWDR;
}

void I2C_stop()
{
	TWCR = nth(TWINT) | nth(TWSTO) | nth(TWEN);	
}