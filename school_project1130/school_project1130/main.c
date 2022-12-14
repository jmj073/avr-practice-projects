/*
 * school_project1130.c
 *
 * Created: 2022-11-30 09:58:54
 * Author : JMJ
 * 
 */

/*
+ components:
	+ ultrasonic:
		+ TC3:
			+ INT0(PD0): ICP3가 있는 PE7은 LCD가 차지하고 있기 때문에
			  대신에 INT0을 사용.
		+ trigger(PD1)
	+ ball switch:
		+ PB0
	+ laser
	+ buzzer:
		+ TC1:
			+ OC1A(PB5)
	+ LCD
*/ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "lcd1602_drv.h"
#include "buzzer.h"
#include "ultrasonic.h"
#include "note.h"
#include "button.h"


static 
void init(void) {
	lcd_init();
	buzzer_init();
	ultrasonic_init();
	btn_init();
}

static
void run() {
	_delay_ms(500);
	
	lcd_clear();
	
	size_t note = rand() % 12;
	lcd_pos_puts(0, 0, NOTE_STR[note]);
	
	uint8_t prev_pressed = btn_pressed();
	ultrasonic_trigger();

	while (1) {

		if (ultrasonic_data_ready()) {
			uint16_t mm = ultrasonic_get();
			ultrasonic_trigger();
			
			buzzer_set_freq(mm);
		}
		
		uint8_t curr_pressed = btn_pressed();
		if (curr_pressed & ~prev_pressed) {
			char freq_str[8];
			uint16_t freq = buzzer_get_freq();
			
			lcd_puts(" ans: ");
			lcd_puts(itoa(NOTE_FREQ[note], freq_str, 10));
			lcd_pos_puts(1, 0, itoa(freq, freq_str, 10));
			
			break;
		}
		
		prev_pressed = curr_pressed;
	}
	
	while (btn_pressed());
	while (!btn_pressed());
	_delay_ms(500);
}

int main(void) {
	init();
	sei();
	
	while (1) {
		run();
	}
}

/* ===================unit test=================== */

/* buzzer */
//int main() {
	//init();
	//
	//sei();
	//
	//while (1) {
		//for (size_t i = 0; i < NOTE_NUM; i++) {
			//buzzer_set_freq(NOTE_FREQ[i]);
			//_delay_ms(500);
		//}
	//}
//}

/* ultrasonic */
//int main() {
	//init();
	//DDRC |= _BV(0);
	//
	//sei();
	//
	//ultrasonic_trigger();
	//
	//while (1) {
		//
		//if (EIFR & _BV(INTF0)) {
			//PORTC |= _BV(0);
		//}
//
		//if (ultrasonic_data_ready()) {
			//uint16_t mm = ultrasonic_get();
			//ultrasonic_trigger();
			//
			//PORTC |= _BV(0);
			//
			//char freq_str[8];
			//lcd_pos_puts(0, 0, itoa(mm, freq_str, 10));
			//_delay_ms(500);
		//}
	//}
//}

/* button */
//int main() {
	//DDRC |= _BV(0);
	//
	//btn_init();
	//
	//while (1) {
		//PORTC = (PORTC & ~_BV(0)) | btn_pressed();
	//}
//}
