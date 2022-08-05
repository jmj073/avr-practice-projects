/*
 * morse_decoder.c
 *
 * Created: 2022-06-19 17:34:38
 *  Author: JMJ
 */ 

#include "morse_decoder.h"

static const char MORSE_TABLE[1 << (MORSE_CODE_MAX_SIZE + 1)] = {
	[0x04] = 'A', [0x17] = 'B', [0x19] = 'C',
	[0x0B] = 'D', [0x01] = 'E', [0x11] = 'F',
	[0x0D] = 'G', [0x0F] = 'H', [0x03] = 'I',
	[0x16] = 'J', [0x0C] = 'K', [0x13] = 'L',
	[0x06] = 'M', [0x05] = 'N', [0x0E] = 'O',
	[0x15] = 'P', [0x1C] = 'Q', [0x09] = 'R',
	[0x07] = 'S', [0x02] = 'T', [0x08] = 'U',
	[0x10] = 'V', [0x0A] = 'W', [0x18] = 'X',
	[0x1A] = 'Y', [0x1B] = 'Z',
	
	[0x3E] = '0', [0x2E] = '1', [0x26] = '2',
	[0x22] = '3', [0x20] = '4', [0x1F] = '5',
	[0x2F] = '6', [0x37] = '7', [0x3B] = '8',
	[0x3D] = '9',
	
	[0x54] = '.', [0x72] = ',', [0x4B] = '?',
	[0x5D] = '\'',[0x6A] = '!', [0x31] = '/',
	[0x35] = '(', [0x6C] = ')', [0x27] = '&',
	[0x77] = ':', [0x69] = ';', [0x30] = '=',
	[0x29] = '+', [0x60] = '-', [0x4C] = '_',
	[0x51] = '"', [0x59] = '@', 
};


// get_rightchild = get_leftchild(parent) + 1
static inline get_leftchild(uint8_t parent) {
	return parent * 2 + 1;
}

// method 1
int MORSE_decode(uint8_t morse_code, uint8_t morse_code_size)
{
	if (morse_code_size > MORSE_CODE_MAX_SIZE) return -1;
	
	uint8_t idx = 0;
	while (morse_code_size-- > 0) {
		idx = get_leftchild(idx) + (morse_code & 1);
		morse_code >>= 1;
	}
	
	return MORSE_TABLE[idx] ?: -1;
}