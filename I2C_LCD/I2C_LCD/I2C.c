/*
 * I2C.c
 *
 * Created: 2021-04-07 오후 1:30:05
 *  Author: kccistc
 */ 
#include "I2C.h"

void I2C_Init(void)
{
	I2C_DDR |= (1<<I2C_SCL) | (1<<I2C_SDA);	//포트 출력으로 설정
	TWBR = 72;		//100khz 의미 (다른 곳에서 계산되있는 통신 속도를 사용)
	//TWBR = 32;	//200khz 의미
	//TWBR = 12;	//400khz 의미
}

void I2C_Start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);		//Send START condition
	while (!(TWCR & (1<<TWINT))) ;					//Wait for TWINT flag set.
													//This indicates that the START condition has been transmitted
}

void I2C_TxData(uint8_t data)
{
	TWDR = data;						//write bit = 0, SLA_W; SLA_W = slave dev 주소 +write, 1byte:dev주소+r/w  //lcd 주소
	TWCR = (1<<TWINT) | (1<<TWEN);		//Load SLA_W into TWDR Register.
										//Clear TWINT bit in TWCR to start transmission of address
	while (!(TWCR & (1<<TWINT))) ;		//Wait for TWINT flag set. This indicates that the
										//SLA+W has been transmitted, and ACK/NACK has been received.
}

void I2C_Stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);		//Transmit STOP condition
}

void I2C_TxByte(uint8_t devAddr_RW, uint8_t data)
{
	/* I2C inteface를 이용한 1byte 전송 코드 */
	//1. start bit 전송
	I2C_Start();
	
	//2. data 전송 (dev address + r/w)
	I2C_TxData(devAddr_RW); //함수 사용, 반복되는 코드가 발생할시 함수 이용

	//3. 실제 데이터 전송
	I2C_TxData(data);
	
	//4. stop bit 전송, 통신 종료
	I2C_Stop();
}