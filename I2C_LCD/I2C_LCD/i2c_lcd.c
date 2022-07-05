/*
 * lcd_8bit.c
 *
 * Created: 2021-04-02 오후 2:25:49
 *  Author: kccistc
 */ 
#include "i2c_lcd.h"

#define LCD_DEV_ADDR_W (0x27<<1)
static uint8_t I2C_LCD_Data;

void LCDCommandMode(void)
{
	//1. cmd rs값을 0으로 출력
	I2C_LCD_Data &= ~(1<<LCD_RS);
}
void LCDDataMode(void)
{
	//cmd rs값을 1으로 출력
	I2C_LCD_Data |= (1<<LCD_RS);
}
void LCDWriteMode(void)
{
	//2. r/w pin값을 0(write)로 출력
	I2C_LCD_Data &= ~(1<<LCD_RW);
}
void LCDSendData(uint8_t data) //8bit mode data
{
	//3. 입력된 data 출력
	LCD_DATA_PORT = data;
}
void LCD_SendData4bit(uint8_t data)
{
	I2C_LCD_Data = (I2C_LCD_Data & 0x0f) | (data & 0xf0);
	LCDEnable();
	I2C_LCD_Data = (I2C_LCD_Data & 0x0f) | ((data & 0x0f)<<4);
	LCDEnable();
}

void LCD_BackLightOn(void)
{
	I2C_LCD_Data |= (1<<LCD_BACKLIGT);
	I2C_TxByte(LCD_DEV_ADDR_W, I2C_LCD_Data);
}
void LCD_BackLightOff(void)
{
	I2C_LCD_Data &= ~(1<<LCD_BACKLIGT);
	I2C_TxByte(LCD_DEV_ADDR_W, I2C_LCD_Data);
}

void LCDEnable(void)
{
	//4. enable pin을 0>1>0 으로 실행
	//LCD_ENABLE_PORT &= ~(1<<LCD_ENABLE);
	//LCD_ENABLE_PORT |= (1<<LCD_ENABLE);
	//LCD_ENABLE_PORT &= ~(1<<LCD_ENABLE);
	
	I2C_LCD_Data &= ~(1<<LCD_ENABLE);
	I2C_TxByte(LCD_DEV_ADDR_W, I2C_LCD_Data);
	I2C_LCD_Data |= (1<<LCD_ENABLE);
	I2C_TxByte(LCD_DEV_ADDR_W, I2C_LCD_Data);
	I2C_LCD_Data &= ~(1<<LCD_ENABLE);
	I2C_TxByte(LCD_DEV_ADDR_W, I2C_LCD_Data);
	
	//딜레이를 줘야 깨지지 않고 나옴
	_delay_us(1800);
}

void LCDWriteCommand(uint8_t cmdData)
{
	
	LCDCommandMode();
	LCDWriteMode();
	LCD_SendData4bit(cmdData);
	//LCDEnable();
}

void LCDWriteData(uint8_t charData)
{
	LCDDataMode();
	LCDWriteMode();
	LCD_SendData4bit(charData);
	//LCDEnable();
}

void LCDInit(void)
{
	//LCD_DATA_DDR =0xff;
	//LCD_RS_DDR |= (1<<LCD_RS);
	//LCD_RW_DDR |= (1<<LCD_RW);
	//LCD_ENABLE_DDR |= (1<<LCD_ENABLE);
	
	I2C_Init();
	
	//_delay_ms(20);
	//LCDWriteCommand(0x03); 
	//_delay_ms(5);
	//LCDWriteCommand(0x03); 
	//_delay_ms(1);
	//LCDWriteCommand(0x03); 
	LCDWriteCommand(0x02); 
	LCDWriteCommand(COMMAND_FUCTION_SET_4BIT); //4bit function set
	//LCDWriteCommand(COMMAND_DISPLAY_OFF); //display off
	LCDWriteCommand(COMMAND_DISPLAY_CLEAR); //display clear
	LCDWriteCommand(COMMAND_ENTRY_MODE_SET); //entry mode set 0b00000110
	LCDWriteCommand(COMMAND_DISPLAY_ON);
	LCD_BackLightOn();
}

void LCDWriteString(char *string)
{
	for(uint8_t i=0;string[i];i++)
	{
		LCDWriteData(string[i]);
	}
}
void LCDGoToXY(uint8_t row, uint8_t col)
{
	col %= 16;
	row %= 2;
	
	uint8_t address = (0x40 * row) + col;
	uint8_t command =0x80 + address;
	LCDWriteCommand(command);
}
void LCDWriteStringXY(uint8_t row, uint8_t col, char *string)
{
	LCDGoToXY(row, col);
	LCDWriteString(string);
}
