#include <avr/io.h>
#include <my_util.h>
#include "../include/I2C.h"
// #include <I2C.h>

void I2C_init()
{
	DDRD |= nth(I2C_SCL) | nth(I2C_SDA);
	
	TWBR = 32; // Ŭ�� ���ļ� ���� 200KHz
}

void I2C_start()
{
	TWCR = nth(TWINT) | nth(TWSTA) | nth(TWEN);
	
	while( !(TWCR & nth(TWINT)) ); // ���� �Ϸ� ���
}

void I2C_transmit(uint8_t data)
{
	TWDR = data;
	
	TWCR = nth(TWINT) | nth(TWEN) | nth(TWEA);
	while ( !(TWCR & nth(TWINT)) ); // ���� �Ϸ� ���
}

uint8_t I2C_receive_ACK()
{
	TWCR = nth(TWINT) | nth(TWEN) | nth(TWEA);
	while ( !(TWCR & nth(TWINT)) ); // ���� �Ϸ� ���

	return TWDR;
}

uint8_t I2C_receive_NACK()
{
	TWCR = nth(TWINT) | nth(TWEN);
	while ( !(TWCR & nth(TWINT)) ); // ���� �Ϸ� ���
	
	return TWDR;
}

void I2C_stop()
{
	TWCR = nth(TWINT) | nth(TWSTO) | nth(TWEN);	
}