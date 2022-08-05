/*
 * morse_decoder.h
 *
 * Created: 2022-06-19 17:34:13
 *  Author: JMJ
 */ 


#ifndef MORSE_DECODER_H_
#define MORSE_DECODER_H_

#include <stdint.h>

#define MORSE_CODE_MAX_SIZE 6

/*
morse code => ascii code
+ return value:
	+ on success: ASCII code
	+ on failure: -1
+ NOTE: 'morse_code' is LSB first
*/
int MORSE_decode(uint8_t morse_code, uint8_t morse_code_size);


#endif /* MORSE DECODER_H_ */