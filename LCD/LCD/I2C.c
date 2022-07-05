#include <avr/io.h>
#include <my_util.h>
//#include "../include/I2C.h"
#include <I2C.h>


void I2C_init(uint32_t KHz)
{
	DDRD |= nth(I2C_SCL) | nth(I2C_SDA);
	TWBR = (F_CPU / (KHz * 1000) - 16) / 2;
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

void I2C_write_byte(u8 addr, u8 byte)
{
	I2C_start();
	I2C_transmit(addr << 1);
	I2C_transmit(byte);
	I2C_stop();
}


void I2C_write(u8 addr, const u8* data, size_t size)
{
	I2C_start();
	I2C_transmit(addr << 1);
	
	while (size-- > 0)
		I2C_transmit(*data++);
	
	I2C_stop();
}

u8 I2C_read_byte(u8 addr)
{
	I2C_start();
	I2C_transmit(addr << 1 | 1);
	
	u8 byte = I2C_receive_NACK();
	I2C_stop();
	
	return byte;
}

void I2C_read(u8 addr, u8* buf, size_t size)
{
	I2C_start();
	I2C_transmit(addr << 1 | 1);
	for (; size > 1; size--)
		*buf++ = I2C_receive_ACK();
	if (size) *buf = I2C_receive_NACK();
	I2C_stop();
}

u8 I2C_find_addr()
{
	I2C_init(100);
	
	uint8_t addr = 1;
	for (; addr < 0x78; addr++) {
		I2C_start();
		I2C_transmit(addr << 1);
		uint8_t status = I2C_status();
		I2C_stop();
		
		if (status == 0x18) break;
	}
	
	return addr;
}