/*	.include "m128adef.inc"

	.cseg
	.org 	0x00
	ldi	r16,(1<<PINB0)		; load 00000001 into register 16
        out     DDRB,r16		; write register 16 to DDRB
        out     PORTB,r16		; write register 16 to PORTB

loop:	rjmp    loop			; stay in infinite loop*/