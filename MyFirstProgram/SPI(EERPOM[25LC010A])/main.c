/*
 * SPI(EERPOM[25LC010A]).c
 *
 * Created: 2022-05-28 22:57:04
 * Author : user
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <UART.h>
#include "EEPROM_25LC010.h"
#include <my_util.h>

FILE OUTPUT = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);

// 마스터 모드
// 클록 극성: 0, 클록 위상: 0
// 클록: 4MHz
void SPI_init()
{
	DDRB |= _BV(SPI_SS) | _BV(SPI_MOSI) | _BV(SPI_SCK);
	DDRB &= ~_BV(SPI_MISO);
	
	PORTB |= _BV(SPI_SS);
	
	SPCR |= _BV(MSTR); // 마스터 모드
	SPCR |= _BV(SPE); // SPI 활성화
}

static void __EEPROM_write(u8 addr, const u8* data, u8 size)
{
	EEPROM_write_enable();
	EEPROM_select();
	EEPROM_swap_byte(EEPROM_WRITE);
	EEPROM_send_addr(addr);
	for (u8 i = 0; i < size; i++)
	EEPROM_swap_byte(data[i]);
	EEPROM_deselect();
	
	while (EEPROM_read_status() & _BV(EEPROM_WIP));
}


int main(void)
{
    UART1_init();
	SPI_init();
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	// -----------------------------------------------
	
	//EEPROM_write_byte(128, 77);
	//printf("%d\n\r", EEPROM_read_byte(128));
	//printf("%d\n\r", EEPROM_read_byte(0));

	// -----------------------------------------------
	
	//u8 page[16];
	//for (u8 i = 0; i < 16; i++)
		//page[i] = i;
	//
	//EEPROM_write_page(8 * EEPROM_PAGE_SIZE, page);
		//
	//for (u8 i = 0; i < 16; i++)
	//printf("%d\n\r", EEPROM_read_byte(0 * EEPROM_PAGE_SIZE + i));
	//for (u8 i = 0; i < 16; i++)
		//printf("%d\n\r", EEPROM_read_byte(8 * EEPROM_PAGE_SIZE + i));

	// -----------------------------------------------

	printf("size: %d\n\r", EEPROM_write(13, "Let's have a good life!", 23));
	
	for (u8 i = 0; i < 23; i++)
		printf("%c", EEPROM_read_byte(13 + i));
	
	loop;
}

	//u8 data[23];
	//for (u8 i = 0; i < 23; i++)
	//data[i] = 23 - i;
//
	//__EEPROM_write(5, data, 3);
	//
	//for (u8 i = 0; i < 3; i++)
	//printf("%d\n\r", EEPROM_read_byte(5 + i));
	
	// 13, 23