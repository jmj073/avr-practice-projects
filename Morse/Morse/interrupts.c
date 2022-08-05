/*
 * interrupts.c
 *
 * Created: 2022-06-13 08:38:26
 *  Author: JMJ
 */

/*
+ interrupts list:
	1. TIMER0_OVF_vect: button polling
	2. TIMER1_COMPA_vect: button time over
	2. TIMER1_COMPB_vect: translation unit time over
*/

#include <avr/interrupt.h>

#include "settings.h"
#include "my_util.h"
#include "pins.h"
#include "timers.h"
#include "task_queue.h"
#include "lcd1602_drv.h"

/* ButtoN */
#define BtN_TIMER_start(cs, comp) TC1_COMPA_start(cs, comp)
#define BtN_TIMER_stop() TC1_COMPA_stop()

/* Translation Unit */
#define TU_TIMER_start(cs, comp) TC1_COMPB_start(cs, comp)
#define TU_TIMER_stop() (TU_TIMER_CNT = 0, TC1_COMPB_stop())

void process_BtN_input(uint16_t);
void process_morse_code(uint16_t);

static uint8_t TU_TIMER_CNT;

/* button polling */
ISR(TIMER0_OVF_vect)
{
	static uint8_t prev;
	uint8_t curr = BUTTON_PRESSED();
	
	if (prev != curr) {
		prev = curr;
		
		if (curr) { // pressed
			LED_ON();
			TU_TIMER_stop();
			BtN_TIMER_start(BtN_TC1_TIMEOVER_CS, BtN_TC1_TIMEOVER_COMP);
		}
		else { // released
			LED_OFF();
			uint8_t is_timeover = BtN_TIMER_stop();
			TASKQ_push((struct task) { process_BtN_input, is_timeover });
			TU_TIMER_start(TU_TC1_TIMEOVER_CS, TU_TC1_TIMEOVER_COMP);
		}
	}
	
}

/* button time over */
ISR(TIMER1_COMPA_vect)
{
	TC1_COMPA_timeover();
	LED_OFF();
}

/* translation unit time over */
ISR(TIMER1_COMPB_vect)
{
	TCNT1 = 0;
	
	lcd_pos_putc(1, LCD_CH_LEN - 1, TU_TIMER_CNT);
	if (++TU_TIMER_CNT >= 8) {
		TU_TIMER_CNT = 0;
		TC1_COMPB_timeover();
		TASKQ_push((struct task) { process_morse_code, 0 });
	}
}