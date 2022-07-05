///*
//* LCD_I2C.c
//*
//*  $Date: 2016-07-13 22:43:46 +0900 (¼ö, 13 7 2016) $
//*  $Rev: 119 $
//*/
//// source(ÃâÃ³): https://embed-avr.tistory.com/53
//// 4bit mode
//
//#define F_CPU 16000000L
//#include <util/delay.h>
//#include <avr/io.h>
//#include <I2C.h>
//#include "lcd1602_drv.h"
//
//#define WAIT_TIME   1
//#define LCD_ADDR 0x27
//
//struct port
//{
	//uint8_t   pin;
	//uint8_t   ddr;
	//uint8_t   port;
//};
//
///* Board dependent code */
//// PORTE
//// 0: RS(0: IR, 1: DR)
//// 1: RW
//// 2: E
//// 3:
//// 4: D4
//// 5: D5
//// 6: D6
//// 7: D7
//
//
///* Internal LCD1602 code */
//static uint8_t lcd_read(void)
//{
	//uint8_t data = 0;
//
	//I2C_write_byte(LCD_ADDR, LCD_RW | LCD_EN);
	//_delay_us(WAIT_TIME);
	//I2C_write_byte(LCD_ADDR, LCD_RW);
	//
	//data = (I2C_read_byte(LCD_ADDR) & 0xF0);
	//
	//I2C_write_byte(LCD_ADDR, LCD_EN);
	//_delay_us(WAIT_TIME);
	//I2C_write_byte(LCD_ADDR, 0);
	//
	//data |= (I2C_read_byte(LCD_ADDR) & 0xF0) >> 4;
//
	//return data;
//}
//
//static uint8_t lcd_wait_busy(void)
//{
	//uint8_t val;
//
	//while ((val = lcd_read()) & BUSY_FLAG);
//
	//return val;
//}
//
//static void lcd_write(uint8_t data, uint8_t rs)
//{
	//lcd_wait_busy();
	//
	//I2C_write_byte(LCD_ADDR, (data & 0xF0) | LCD_EN | rs);
	//_delay_us(WAIT_TIME);
	//I2C_write_byte(LCD_ADDR, 0);
	//
	//I2C_write_byte(LCD_ADDR, ((data << 4) & 0xF0) | LCD_EN | rs);
	//_delay_us(WAIT_TIME);
	//I2C_write_byte(LCD_ADDR, 0);
//}
//
//static inline void send_cmd(uint8_t cmd)
//{
	//lcd_write(cmd, 0);
//}
//static inline void send_data(uint8_t data)
//{
	//lcd_write(data, LCD_RS);
//}
//
///* LCD1602 API code */
//void lcd_init(void)
//{
	//I2C_init(50); // 50KHz
//
	//_delay_ms(100);
	//I2C_write_byte(LCD_ADDR, CMD_FUNC | DATA_8BIT | LCD_EN);
	//_delay_us(WAIT_TIME);
	//I2C_write_byte(LCD_ADDR, 0);
	//_delay_ms(1);
	//I2C_write_byte(LCD_ADDR, CMD_FUNC | LCD_EN);
	//_delay_us(WAIT_TIME);
	//I2C_write_byte(LCD_ADDR, 0);
//
	//send_cmd(CMD_FUNC | TWO_LINE);
	//send_cmd(CMD_ONOFF);
	//send_cmd(CMD_CLR);
	//send_cmd(CMD_HOME);
	//send_cmd(CMD_MODE | CURSOR_INC);
	//send_cmd(CMD_ONOFF | DISPLAY_ON);
//}
//
//void lcd_putc(char ch)
//{
	//uint8_t pos = lcd_wait_busy();
	//uint8_t addr = 0;
//
	//if (ch == '\n')
	//{
		//if (pos < LCD_START_LINE2)
		//addr = LCD_START_LINE2;
		//else
		//addr = LCD_START_LINE1;
		//send_cmd(DDRAM_ADDR | addr);
	//}
	//else
	//{
		//if (pos == LCD_START_LINE1 + LCD_CH_LEN)
		//send_cmd(DDRAM_ADDR | LCD_START_LINE2);
		//else if (pos == LCD_START_LINE2 + LCD_CH_LEN)
		//send_cmd(DDRAM_ADDR | LCD_START_LINE1);
	//}
	//
	//send_data(ch);
//}
//
//void lcd_puts(const char *str)
//{
	//while (*str)
	//lcd_putc(*str++);
//}
//
//void lcd_pos(uint8_t row, uint8_t col)
//{
	//if (row)
	//send_cmd(DDRAM_ADDR | (LCD_START_LINE2 + col));
	//else
	//send_cmd(DDRAM_ADDR | (LCD_START_LINE1 + col));
//}
//
//void lcd_pos_putc(uint8_t row, uint8_t col, char ch)
//{
	//lcd_pos(row, col);
	//lcd_putc(ch);
//}
//
//void lcd_pos_puts(uint8_t row, uint8_t col, const char *str)
//{
	//lcd_pos(row, col);
	//lcd_puts(str);
//}
//
//void lcd_CG_write(uint8_t addr, const uint8_t* graphics)
//{
	//send_cmd(CGRAM_ADDR | ((addr & 7) << 3));
	//for (uint8_t i = 0; i < 8; i++)
	//send_data(*graphics++);
	//send_cmd(CMD_HOME);
//}
//
//void lcd_clear()
//{
	//send_cmd(CMD_CLR);
//}