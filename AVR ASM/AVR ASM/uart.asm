;.include "m128adef.inc"
;.include "util.inc"
;
;#define F_CPU 16000000
;
;.equ baud	= 9600						; baud
;.equ bps	= (F_CPU / 16 / baud) - 1	; baud prescale
;
;
;.cseg
;.org	0x0000
;
;	setStack RAMEND, r16
;
;	ldi		r16,		LOW(RAMEND)
;	ldi		r17,		HIGH(RAMEND)
;
;	ldi		r16,		LOW(bps)
;	ldi		r17,		HIGH(bps)
;	call	uart1_init
;
;	ldi		ZL,			LOW(my_str * 2)
;	ldi		ZH,			HIGH(my_str * 2)
;	call	uart1_puts
;
;forever:
;	rjmp	forever
;
;uart1_init:; arg: none
;	sts		UBRR1L,		r16
;	sts		UBRR1H,		r17
;
;	ldi		r16,		(1<<RXEN1) | (1<<TXEN1)
;	sts		UCSR1B,		r16
;
;	ret
;
;uart1_putc:; arg: character(r16)
;	lds		r17,		UCSR1A
;	sbrs	r17,		UDRE1
;	rjmp	uart1_putc
;
;	sts		UDR1,		r16
;
;	ret
;
;uart1_puts:; arg: string(Z)
;	lpm		r16,		Z+
;	tst		r16
;	breq	uart1_puts_end
;
;uart1_puts_wait:
;	lds		r17,		UCSR1A
;	sbrs	r17,		UDRE1
;	rjmp	uart1_puts_wait
;
;	sts		UDR1,		r16
;	rjmp	uart1_puts
;
;uart1_puts_end:
;	ret
;
;uart1_getc:
;	lds		r17,		UCSR1A
;	sbrs	r17,		RXC1
;	rjmp	uart1_getc
;
;	lds		r16,		UDR1
;
;	ret
;
;uart1_gets:
;	lds		r17,		UCSR1A
;	sbrs	r17,		RXC1
;	rjmp	uart1_gets
;
;	lds		r16,		UDR1
;
;	cpi		r16,		'\r'
;	breq	uart1_gets_end
;
;	st		X+,			r16
;	rjmp	uart1_gets
;
;uart1_gets_end:
;	ret
;
;
;; data
;
;my_str: .db		"hello", '\0'