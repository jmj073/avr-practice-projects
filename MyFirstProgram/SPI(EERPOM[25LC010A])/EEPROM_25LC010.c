/*
 * EEPROM_25LC010.c
 *
 * Created: 2022-05-28 22:59:43
 *  Author: JMJ
 */ 

#include <avr/sfr_defs.h>
#include <my_util.h>
#include "EEPROM_25LC010.h"

void EEPROM_swap_byte(u8 byte)
{
	SPDR = byte;
	while (!(SPSR & _BV(SPIF)));
}

void EEPROM_send_addr(u8 addr)
{
	EEPROM_swap_byte(addr);
}

// read================================================

u8 EEPROM_read_status()
{
	EEPROM_select();
	EEPROM_swap_byte(EEPROM_RDSR);
	EEPROM_swap_byte(0);
	EEPROM_deselect();
	
	return SPDR;
}

u8 EEPROM_read_byte(u8 addr)
{
	EEPROM_select();
	EEPROM_swap_byte(EEPROM_READ);
	EEPROM_send_addr(addr);
	EEPROM_swap_byte(0);
	EEPROM_deselect();
	
	return SPDR;
}

u8 EEPROM_read(u8 addr, u8* buf, u8 size)
{
	size = min(size, EEPROM_TOTAL_SIZE);
	
	for (u8 i = 0; i < size; i++)
		buf[i] = EEPROM_read_byte(addr + i);
	
	return size;
}

// write===============================================

void EEPROM_write_enable()
{
	EEPROM_select();
	EEPROM_swap_byte(EEPROM_WREN);
	EEPROM_deselect();
}

void EEPROM_write_byte(u8 addr, u8 byte)
{
	EEPROM_write_enable();
	
	EEPROM_select();
	EEPROM_swap_byte(EEPROM_WRITE);
	EEPROM_send_addr(addr);
	EEPROM_swap_byte(byte);
	EEPROM_deselect();
	
	while (EEPROM_read_status() & _BV(EEPROM_WIP));
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

void EEPROM_write_page(u8 page_addr, const u8* page)
{
	__EEPROM_write(page_addr, page, 16);
}

u8 EEPROM_write(u8 addr, const u8* data, u8 size)
{
	if (addr >= EEPROM_TOTAL_SIZE || !size) return 0;
	u8 written = min(size, EEPROM_TOTAL_SIZE - addr);
	u8 cur = written;
	u8 aligned = round_align(addr, EEPROM_PAGE_SIZE);
	
	if (aligned - addr) {
		u8 sz = min(aligned - addr, cur);
		__EEPROM_write(addr, data, sz);
		data += sz;
		cur -= sz;
	}
	
	while (cur >= EEPROM_PAGE_SIZE) {
		EEPROM_write_page(aligned, data);
		cur -= EEPROM_PAGE_SIZE;
		data += EEPROM_PAGE_SIZE;
		aligned += EEPROM_PAGE_SIZE;
	}
	
	if (cur)
		__EEPROM_write(aligned, data, cur);
	
	return written;
}


void EEPROM_erase_all()
{
	for (uint8_t page_addr = 0;
		page_addr < EEPROM_TOTAL_SIZE; 
		page_addr += EEPROM_PAGE_SIZE) 
	 {
		u8 page[16] = { 0, };
		EEPROM_write_page(page_addr, page);
	}
}