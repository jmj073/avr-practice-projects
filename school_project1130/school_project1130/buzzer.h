/*
 * buzzer.h
 *
 * Created: 2022-11-30 10:14:10
 *  Author: user
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#include <stdint.h>

void buzzer_init(void);
void buzzer_set_freq(uint16_t freq);
uint16_t buzzer_get_freq(void);


#endif /* BUZZER_H_ */