/*
 * note.c
 *
 * Created: 2022-12-14 10:04:10
 *  Author: user
 */ 

#include "note.h"

const uint16_t NOTE_FREQ[NOTE_NUM] = {
	NOTE3_C	  ,
	NOTE3_CS  ,
	NOTE3_D	  ,
	NOTE3_DS  ,
	NOTE3_E	  ,
	NOTE3_F	  ,
	NOTE3_FS  ,
	NOTE3_G	  ,
	NOTE3_GS  ,
	NOTE3_A	  ,
	NOTE3_AS  ,
	NOTE3_B	  ,
};


const char* NOTE_STR[NOTE_NUM] = {
	"C"	,
	"C#",
	"D"	,
	"D#",
	"E"	,
	"F"	,
	"F#",
	"G"	,
	"G#",
	"A"	,
	"A#",
	"B"	,
};
