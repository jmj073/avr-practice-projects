/*
 * lcd1602_drv.h
 *
 *  $Date: 2016-07-13 21:50:16 +0900 (수, 13 7 2016) $
 *  $Rev: 118 $
 */ 
// source(출처): https://embed-avr.tistory.com/53

#ifndef __LCD1602_DRV_H__
#define __LCD1602_DRV_H__

#include <stdint.h> 

/* LCD PORT* */
#define LCD_PORT &PINE

/* Board dependent */
#define LCD_RS      0x01
#define LCD_RW      0x02
#define LCD_EN      0x04

/* LCD Command Set */
#define CMD_CLR     0x01
#define CMD_HOME    0x02
#define CMD_MODE    0x04
#define CMD_ONOFF   0x08
#define CMD_SHIFT   0x10
#define CMD_FUNC    0x20
#define CGRAM_ADDR  0x40
#define DDRAM_ADDR  0x80

/* Entry Mode Set */
#define DISP_SHIFT  0x01
#define CURSOR_INC  0x02

/* Display On/Off Control */
#define BLINK_ON    0x01
#define CURSOR_ON   0x02
#define DISPLAY_ON  0x04

/* Cursor or Display Shift */
#define CURSOR_R    0x04
#define CUR_SHIFT   0x08


/* Function set */
#define FONT_5x10   0x04
#define TWO_LINE    0x08
#define DATA_8BIT   0x10

#define BUSY_FLAG   0x80

#define LCD_CH_LEN      16
#define LCD_START_LINE1 0x00
#define LCD_START_LINE2 0x40

/* LCD CHARACTER */
#define LCDC_EMPTY 0x20
#define LCDC_DOT 0xA5
#define LCDC_DASH 0xB0


// 4bit mode
void lcd_init(void);
void lcd_putc(char ch);
void lcd_puts(const char *str);
void lcd_pos(uint8_t row, uint8_t col);
void lcd_pos_putc(uint8_t row, uint8_t col, char ch);
void lcd_pos_puts(uint8_t row, uint8_t col, const char *str);
void lcd_CG_write(uint8_t addr, const uint8_t *graphics);
void lcd_clear();

#endif /* __LCD1602_DRV_H__ */