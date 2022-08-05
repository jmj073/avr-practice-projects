/*
 * settings.h
 *
 * Created: 2022-06-19 15:53:18
 *  Author: user
 */ 


#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <avr/io.h>

// 분주비 1024, 약 0.5초 후에 타임 오버
#define BtN_TC1_TIMEOVER_CS (_BV(CS12) | _BV(CS10))
#define BtN_TC1_TIMEOVER_COMP (0.4 * F_CPU / 1024)

/* 
+ Translation Unit 
모스부호 입력의 문자 구분 기준 시간을 정하는데 사용됨
8로 나누는 이유는 LCD 8칸으로 남은 시간을 표현하기 때문
*/
#define TU_TC1_TIMEOVER_CS (_BV(CS12) | _BV(CS10))
#define TU_TC1_TIMEOVER_COMP (1.0 / 8 * F_CPU / 1024)

#endif /* SETTINGS_H_ */