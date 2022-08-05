/*
 * settings.h
 *
 * Created: 2022-06-19 15:53:18
 *  Author: user
 */ 


#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <avr/io.h>

// ���ֺ� 1024, �� 0.5�� �Ŀ� Ÿ�� ����
#define BtN_TC1_TIMEOVER_CS (_BV(CS12) | _BV(CS10))
#define BtN_TC1_TIMEOVER_COMP (0.4 * F_CPU / 1024)

/* 
+ Translation Unit 
�𽺺�ȣ �Է��� ���� ���� ���� �ð��� ���ϴµ� ����
8�� ������ ������ LCD 8ĭ���� ���� �ð��� ǥ���ϱ� ����
*/
#define TU_TC1_TIMEOVER_CS (_BV(CS12) | _BV(CS10))
#define TU_TC1_TIMEOVER_COMP (1.0 / 8 * F_CPU / 1024)

#endif /* SETTINGS_H_ */