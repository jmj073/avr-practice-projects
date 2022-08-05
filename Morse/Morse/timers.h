/*
 * timers.h
 *
 * Created: 2022-06-13 09:27:32
 *  Author: JMJ
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

#include <stdint.h>

void TC1_COMPA_start(uint8_t CS, uint16_t COMP);
uint8_t TC1_COMPA_stop();
void TC1_COMPA_timeover();

void TC1_COMPB_start(uint8_t CS, uint16_t COMP);
uint8_t TC1_COMPB_stop();
void TC1_COMPB_timeover();


#endif /* TIMERS_H_ */