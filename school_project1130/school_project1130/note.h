/*
 * note.h
 *
 * Created: 2022-12-14 10:03:40
 *  Author: user
 */ 


#ifndef NOTE_H_
#define NOTE_H_

#include <stdint.h>

#define NOTE_NUM	12

#define NOTE3_C		131
#define NOTE3_CS	139
#define NOTE3_D		147
#define NOTE3_DS	156
#define NOTE3_E		165
#define NOTE3_F		174
#define NOTE3_FS	185
#define NOTE3_G		196
#define NOTE3_GS	208
#define NOTE3_A		220
#define NOTE3_AS	233
#define NOTE3_B		245


const uint16_t NOTE_FREQ[NOTE_NUM];
const char* NOTE_STR[NOTE_NUM];

#endif /* NOTE_H_ */