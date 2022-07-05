/*
* lcd1602_drv.c
*
*  $Date: 2016-07-13 22:43:46 +0900 (수, 13 7 2016) $
*  $Rev: 119 $
*/
// source(출처): https://embed-avr.tistory.com/53
// 4bit mode

#define F_CPU 16000000L
#include <util/delay.h>
#include <avr/io.h>
#include "lcd1602_drv.h"

#define WAIT_TIME   1

struct port
{
	uint8_t   pin;
	uint8_t   ddr;
	uint8_t   port;
};

/* Board dependent code */
// PORTE
// 0: RS(0: IR, 1: DR)
// 1: RW
// 2: E
// 3:
// 4: D4
// 5: D5
// 6: D6
// 7: D7
volatile struct port *const portd = (void*)&PINE;

static void port_init(void)
{
	portd->port = 0;
	portd->ddr  = (LCD_EN | LCD_RW | LCD_RS | 0xF0);
}

static inline uint8_t port_rd(void)
{
	return portd->pin;
}
static inline void port_wr(uint8_t val)
{
	portd->port = val;
}
static inline void en_high(void)
{
	portd->port |= LCD_EN;
}
static inline void en_low(void)
{
	portd->port &= ~LCD_EN;
}
static inline void set_rd(void)
{
	portd->ddr &= ~0xF0;
	portd->port |= LCD_RW;
}
static inline void set_wr(void)
{
	portd->ddr |= 0xF0;
	portd->port &= ~LCD_RW;
}
static inline void rs_high(void)
{
	portd->port |= LCD_RS;
}
static inline void rs_low(void)
{
	portd->port &= ~LCD_RS;
}
static inline void toggle_en(void)
{
	en_high();
	_delay_us(WAIT_TIME);
	en_low();
}


/* Internal LCD1602 code */
static uint8_t lcd_read(void)
{
	uint8_t data = 0;

	rs_low();
	set_rd();
	toggle_en();
	data = (port_rd() & 0xF0);
	toggle_en();
	data |= (port_rd() & 0xF0) >> 4;

	return data;
}

static uint8_t lcd_wait_busy(void)
{
	uint8_t val;

	while ((val = lcd_read()) & BUSY_FLAG);

	return val;
}

static void lcd_write(uint8_t data, uint8_t rs)
{
	uint8_t cur = 0;

	lcd_wait_busy();

	if (rs)
		rs_high();
	else
		rs_low();

	set_wr();
	cur = portd->port & 0x0F;
	_delay_us(WAIT_TIME);
	port_wr((data & 0xF0) | cur);
	toggle_en();
	port_wr(((data << 4) & 0xF0) | cur);
	toggle_en();
}

static inline void send_cmd(uint8_t cmd)
{
	lcd_write(cmd, 0);
}
static inline void send_data(uint8_t data)
{
	lcd_write(data, 1);
}

/* LCD1602 API code */
void lcd_init(void)
{
	port_init();

	_delay_ms(100);
	rs_low();
	set_wr();
	port_wr(CMD_FUNC | DATA_8BIT);
	toggle_en();
	_delay_ms(5);
	toggle_en();
	_delay_ms(1);
	toggle_en();
	_delay_ms(1);
	port_wr(CMD_FUNC);
	toggle_en();

	send_cmd(CMD_FUNC | TWO_LINE);
	send_cmd(CMD_ONOFF);
	send_cmd(CMD_CLR);
	send_cmd(CMD_HOME);
	send_cmd(CMD_MODE | CURSOR_INC);
	send_cmd(CMD_ONOFF | DISPLAY_ON);
}

void lcd_putc(char ch)
{
	uint8_t pos = lcd_wait_busy();
	uint8_t addr = 0;

	if (ch == '\n')
	{
		if (pos < LCD_START_LINE2)
			addr = LCD_START_LINE2;
		else
			addr = LCD_START_LINE1;
		send_cmd(DDRAM_ADDR | addr);
	}
	else
	{
		if (pos == LCD_START_LINE1 + LCD_CH_LEN)
			send_cmd(DDRAM_ADDR | LCD_START_LINE2);
		else if (pos == LCD_START_LINE2 + LCD_CH_LEN)
			send_cmd(DDRAM_ADDR | LCD_START_LINE1);

		send_data(ch);
	}
}

void lcd_puts(const char *str)
{
	while (*str)
	lcd_putc(*str++);
}

void lcd_pos(uint8_t row, uint8_t col)
{
	if (row)
		send_cmd(DDRAM_ADDR | (LCD_START_LINE2 + col));
	else
		send_cmd(DDRAM_ADDR | (LCD_START_LINE1 + col));
}

void lcd_pos_putc(uint8_t row, uint8_t col, char ch)
{
	lcd_pos(row, col);
	lcd_putc(ch);
}

void lcd_pos_puts(uint8_t row, uint8_t col, const char *str)
{
	lcd_pos(row, col);
	lcd_puts(str);
}

void lcd_CG_write(uint8_t addr, const uint8_t* graphics)
{
	send_cmd(CGRAM_ADDR | ((addr & 7) << 3));
	for (uint8_t i = 0; i < 8; i++)
		send_data(*graphics++);
	send_cmd(CMD_HOME);
}

void lcd_clear()
{
	send_cmd(CMD_CLR);
}