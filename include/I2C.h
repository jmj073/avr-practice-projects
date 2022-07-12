#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include <stdint.h>
#include <stddef.h>

typedef uint8_t u8;

#define I2C_SCL PORTD0
#define I2C_SDA PORTD1

#define I2C_status() (TWSR & 0xF8)

// basic function
void I2C_init(uint32_t KHz); // 30 < KHz 
void I2C_start();
void I2C_transmit(u8 data);
u8 I2C_receive_ACK();
u8 I2C_receive_NACK();
void I2C_stop();

void I2C_write_byte(u8 addr, u8 byte); // no check
void I2C_write(u8 addr, const u8* data, size_t size); // no check
u8 I2C_read_byte(u8 addr);
void I2C_read(u8 addr, u8* buf, size_t size);

u8 I2C_find_addr(); // 슬레이브는 하나만 연결되어 있어야함!

#endif /* I2C_H_ */