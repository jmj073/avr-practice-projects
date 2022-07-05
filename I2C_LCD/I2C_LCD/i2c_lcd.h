/*
 * lcd_8bit.h
 *
 * Created: 2021-04-02 오후 2:26:04
 *  Author: kccistc
 */ 


#ifndef LCD_8BIT_H_
#define LCD_8BIT_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"

#define LCD_DATA_DDR DDRC
#define LCD_DATA_PORT PORTC

#define LCD_RS_DDR DDRB
#define LCD_RS_PORT PORTB
#define LCD_RS		0

#define LCD_RW_DDR DDRB
#define LCD_RW_PORT PORTB
#define LCD_RW		1

#define LCD_ENABLE_DDR DDRB
#define LCD_ENABLE_PORT PORTB
#define LCD_ENABLE	2
#define LCD_BACKLIGT 3

#define COMMAND_FUCTION_SET_8BIT 0x38
#define COMMAND_FUCTION_SET_4BIT 0x28
#define COMMAND_DISPLAY_OFF 0x08
#define COMMAND_DISPLAY_CLEAR 0x01
#define COMMAND_ENTRY_MODE_SET 0x06
#define COMMAND_DISPLAY_ON 0x0c

void LCDCommandMode(void);
void LCDDataMode(void);
void LCDWriteMode(void);
void LCDSendData(uint8_t data);
void LCDEnable(void);

void LCDWriteCommand(uint8_t cmdData);
void LCDWriteData(uint8_t charData);

void LCDInit(void);

void LCDWriteString(char *string);
void LCDGoToXY(uint8_t row, uint8_t col);
void LCDWriteStringXY(uint8_t row, uint8_t col, char *string);

void LCD_SendData4bit(uint8_t data);
void LCD_BackLightOn(void);
void LCD_BackLightOff(void);
#endif /* LCD_8BIT_H_ */