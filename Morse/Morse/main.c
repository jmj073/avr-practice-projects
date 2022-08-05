/*
 * Morse.c
 *
 * Created: 2022-06-11 22:51:23
 * Author : JMJ
 */ 

/*
+ peripherals: 3종류, 3개
	+ BUTTON[1]: 모스부호 입력
	+ LED[1]: 
		+ 켜질때: 버튼 누를 때.
		+ 꺼질때: 버튼을 풀거나 
		  긴 신호의 기준치 시간에 도달했을 때.
	+ LCD[1]: 모스부호 해독 결과 출력
*/

#include <avr/io.h>
#include <avr/interrupt.h>

#include "my_util.h"
#include "pins.h"
#include "lcd1602_drv.h"
#include "timers.h"
#include "task_queue.h"
#include "morse_decoder.h"

#define SUCCEDED_MESSAGE	"succeded"
#define FAILED_MESSAGE		"failed"

// init===================================================

static inline void BUTTON_port_init()
{
	BUTTON_clb(DDR); // input mode
	BUTTON_seb(PORT); // built-in pull-up
}

static inline void LED_port_init() {
	LED_seb(DDR);
}

static inline void TC0_BUTTON_POLL_init()
{
	// timer0
	// 16.384ms (1024 * 256 / F_CPU)
	_Static_assert(F_CPU == 16000000L,
	"Change the value appropriately for F_CPU");
	
	TCCR0 |= _BV(CS02) | _BV(CS01) | _BV(CS00);	// 분주비 1024
	TIMSK |= _BV(TOIE0);			// OVF interrupt enable
}

static inline void lcd_custom_char_init() {
	for (uint8_t i = 0; i < 8; i++) {
		uint8_t graphics[8];
		for (uint8_t j = 0; j < i + 1; j++)
		graphics[j] = 0x00;
		for (uint8_t j = i + 1; j < 8; j++)
		graphics[j] = 0xFF;
		
		lcd_CG_write(i, graphics);
	}
}

static void init()
{
	BUTTON_port_init();
	LED_port_init();
	lcd_init();
	lcd_custom_char_init();
	TC0_BUTTON_POLL_init();
}

// =======================================================

void lcd_line_clear(uint8_t row) {
	lcd_pos(row, 0);
	for (uint8_t i = 0; i < LCD_CH_LEN; i++)
		lcd_putc(LCDC_EMPTY);
	lcd_pos(row, 0);	
}

static volatile uint8_t morse_code, morse_code_size;

void process_BtN_input(uint16_t input)
{
	uint8_t sz = morse_code_size;
	if (sz >= MORSE_CODE_MAX_SIZE) {
		lcd_pos_puts(1, 0, FAILED_MESSAGE);
		morse_code = morse_code_size = 0;
		return;
	}
	
	if (sz == 0) lcd_line_clear(1);
	
	lcd_pos_putc(1, sz, input ? LCDC_DASH : LCDC_DOT);
	if (input) morse_code |= _BV(sz);
	morse_code_size = sz + 1;
}

void process_morse_code(uint16_t not_used)
{
	static uint8_t col_pos; (void)not_used;
	
	int ascii = MORSE_decode(morse_code, morse_code_size);
	morse_code = morse_code_size = 0;
	if (ascii == -1) {
		lcd_pos_puts(1, 0, FAILED_MESSAGE);
		return;
	}
	
	lcd_pos_puts(1, 0, SUCCEDED_MESSAGE);
	if (col_pos >= 16) {
		lcd_line_clear(0);
		col_pos = 0;
	}
	lcd_pos_putc(0, col_pos, ascii);
	col_pos++;
}

int main(void)
{
	init();
	sei();
	
	loop {
		if (!TASKQ_empty()) {
			struct task task = TASKQ_pop_atomic();
			if (task.func) task.func(task.arg);
		}
	}
}

// unit tests======================================================

#include <util/delay.h>


// button polling timer unit test==================================
#if 0

void process_BtN_input(uint16_t input) {
	lcd_line_clear(1);
	if (input)
		lcd_pos_puts(1, 0, "timeover!");
	else
		lcd_pos_puts(1, 0, "no!");
}

#endif // button polling test

// lcd_line_clear test=============================================

//int main() {
	//lcd_init();
	//
	//loop {
		//lcd_line_clear(0);
		//lcd_line_clear(1);
		//lcd_pos_putc(0, 0, '0');
		//lcd_pos_putc(1, 1, '1');
		//lcd_pos_putc(0, 2, '2');
		//lcd_pos_putc(1, 3, '3');
		//lcd_pos_putc(0, 4, '4');
		//_delay_ms(500);
		//
		//lcd_line_clear(1);
		//lcd_line_clear(0);
		////lcd_pos_putc(1, 6, CHAR_EMPTY);
		////_delay_ms(1);
		//lcd_pos_putc(0, 5, '5');
		//lcd_pos_putc(1, 6, '6');
		//lcd_pos_putc(0, 7, '7');
		//lcd_pos_putc(1, 8, '8');
		//lcd_pos_putc(0, 9, '9');
		//_delay_ms(500);
	//}
//}