/*
 * EEPROM_25LC010.h
 *
 * Created: 2022-05-28 22:59:08
 *  Author: JMJ
 */ 
// 주의! 메모리 접근 주소 범위 체크 같은거 없음


#ifndef EEPROM_25LC010_H_
#define EEPROM_25LC010_H_

#include <avr/io.h>
#include <stdint.h>

typedef uint8_t u8;

// [SPI] pin
#define SPI_SS		PORTB0
#define SPI_MOSI	PORTB2
#define SPI_MISO	PORTB3
#define SPI_SCK		PORTB1

// slave select
#define EEPROM_select() (PORTB &= ~(1 << SPI_SS))
#define EEPROM_deselect() (PORTB |= (1 << SPI_SS))

// instruction
#define EEPROM_READ 0x03	// 읽기
#define EEPROM_WRITE 0x02	// 쓰기
#define EEPROM_WREN 0x06	// 쓰기 허용
#define EEPROM_RDSR 0x05	// 상태 레지스터 읽기

// EEPROM status register bits
#define EEPROM_WIP 0 // Write In Progress
#define EEPROM_WEL 1 // Write Enable Latch
#define EEPROM_BP0 2 // Write Protection
#define EEPROM_BP1 3 // Write Protection

#define EEPROM_PAGE_SIZE 16 // (byte)
#define EEPROM_TOTAL_SIZE 128 // (byte)

#define EEPROM_valid_addr(addr) ((addr) <= EEPROM_TOTAL_SIZE)
#define EEPROM_page_aligned(addr) ((addr) % EEPROM_PAGE_SIZE)

void EEPROM_swap_byte(u8 byte);
void EEPROM_send_addr(u8 addr);

u8 EEPROM_read_status();
u8 EEPROM_read_byte(u8 addr);
u8 EEPROM_read(u8 addr, u8* buf, u8 size);

void EEPROM_write_enable();
void EEPROM_write_byte(u8 addr, u8 byte);
void EEPROM_write_page(u8 page_addr, const u8* page);
u8 EEPROM_write(u8 addr, const u8* data, u8 size);

void EEPROM_erase_all();


#endif /* EEPROM_25LC010_H_ */