/*
 * I2C.h
 *
 * Created: 2021-04-07 오후 1:30:16
 *  Author: kccistc
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

#define I2C_DDR DDRD
#define I2C_SCL	PD0
#define I2C_SDA PD1

#define SLAVE_ADDR	0x27<1
#define CLCD_W		SLAVE_ADDR+0
#define CLCD_R		SLAVE_ADDR+1

void I2C_Init(void);
void I2C_Start(void);
void I2C_TxData(uint8_t data);
void I2C_Stop(void);
void I2C_TxByte(uint8_t devAddr_RW, uint8_t data);

#endif /* I2C_H_ */