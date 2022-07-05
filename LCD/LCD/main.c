///*
 //* LCD.c
 //*
 //* Created: 2022-05-17 11:03:46
 //* Author : JMJ
 //*/ 
//
//#define F_CPU 16000000L
//#include <avr/io.h>
//#include <util/delay.h>
//#include <stddef.h>
//
//#define nth(n) (1 << (n))
//#define DATA_MSK 0xF0
//#define RS 0
//#define RW 1
//#define E 2
//
//void LCD_init();
//void command(uint8_t byte);
//void data(uint8_t byte);
//void put_str(const uint8_t* str);
//void set_CGaddr(uint8_t addr);
//void set_DDaddr(uint8_t addr);
//
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
//uint8_t arr[] = { 0x00 ,0x00 ,0x0A, 0x00, 0x11, 0xE, 0x00, 0x00 };
//
//int main() {
	//DDRE = 0xFF;
	//PORTE = 0x00;
	//
	//LCD_init();
	//
	//put_str("My name is 12345");
	//
	//for (uint8_t i = 0; i < 8; i++) {
		//set_CGaddr(i);
		//data(arr[i]);
	//}
	//
	//while (1);
//}
//
//void LCD_init() {
	//_delay_ms(30);
	//command(0x20);
	//_delay_ms(39);
	//command(0x20);
	//_delay_ms(1.53);
	//command(0x20);
	//
	//command(0x28); // function set TWO LINE
	//command(0x06); // entry mode set
	//command(0x01); // all clear
	//command(0x0C); // display on
//}
//
//static inline void lcd(uint8_t byte, uint8_t rs)
//{
	//_delay_ms(2);
	//PORTE = (byte & 0xF0);
	//PORTE = (PORTE & ~0x01) | (rs ? nth(RS) : 0x00); // RS(0):0 or 1 instruction or data 모드
	//PORTE &= 0xFD; // R/W(1):0 write 모드
	//_delay_us(1);
	//PORTE |= 0x04; // E(2):1 Enable(활성화)
	//_delay_us(1);
	//PORTE &= ~0x04; // E(2):0 Disable(비활성화)
	//
	//
	//PORTE = ((byte << 4) & 0xF0);
	//PORTE = (PORTE & ~0x01) | (rs ? 0x01 : 0x00); // RS(0):0 or 1 instruction or data 모드
	//PORTE &= 0xFD; // R/W(1):0 write 모드
	//_delay_us(1);
	//PORTE |= 0x04; // E(2):1 Enable(활성화)
	//_delay_us(1);
	//PORTE &= ~0x04; // E(2):0 Disable(비활성화)
//}
//
//void command(uint8_t byte) {
	//lcd(byte, 0);
//}
//
//void data(uint8_t byte) {
	//lcd(byte, 1);
//}
//
//void put_str(const uint8_t* str) {
	//while (*str) data(*str++);
//}
//
//void set_CGaddr(uint8_t addr) {
	//PORTE = 0x40 | (addr & 0x30);
	//_delay_us(1);
	//PORTE |= 0x04; // E(2):1 Enable(활성화)
	//_delay_us(1);
	//PORTE &= ~0x04; // E(2):0 Disable(비활성화)
	//
	//PORTE = 0x40 | ((addr << 2) & 0x30);
	//_delay_us(1);
	//PORTE |= 0x04; // E(2):1 Enable(활성화)
	//_delay_us(1);
	//PORTE &= ~0x04; // E(2):0 Disable(비활성화)
	//
	//PORTE = 0x40 | ((addr << 2) & 0x30);
	//_delay_us(1);
	//PORTE |= 0x04; // E(2):1 Enable(활성화)
	//_delay_us(1);
	//PORTE &= ~0x04; // E(2):0 Disable(비활성화)
//}
//
//void set_DDaddr(uint8_t addr) {
	//
//}

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <my_util.h>
#include "lcd1602_drv.h"

const uint8_t empty_heart[8] = {	0x0,0xa,0x15,0x11,0xa,0x4,0x0, 0x0 }; 
const uint8_t filled_heart[8] = { 0x0,0xa,0x1f,0x1f,0xe,0x4,0x0, 0x0 };
	

int main() {
	lcd_init();
	lcd_CG_write(1, empty_heart);
	lcd_CG_write(2, filled_heart);
	
	uint8_t cur_ch = 1;
	loop {
		lcd_pos(0, 0);
		lcd_clear();
		
		for (uint8_t i = 0; i < 16; i++)
			lcd_putc(cur_ch);
		lcd_putc('\n');
		for (uint8_t i = 0; i < 16; i++)
			lcd_putc(cur_ch);
		_delay_ms(1000);
		cur_ch ^= 3;
	}
}