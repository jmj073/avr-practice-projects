.include "m128adef.inc"

.def mask		= r16
.def ledR		= r17
.def loopCt		= r18
.def iLoopRl	= r24
.def iLoopRh	= r25

.equ iVal		= 39998


.cseg
.org 0x00

	; initialize stack pointer
	ldi		r16,	LOW(RAMEND)
	out		SPL,	r16
	ldi		r16,	HIGH(RAMEND)
	out		SPH,	r16

	clr		ledR
	ldi		mask,	(1 << PINB0)
	out		DDRB,	mask

start:
	eor		ledR,	mask
	out		PORTB,	ledR

	ldi		loopCt,		50
	rcall	delay10ms

	rjmp	start

delay10ms:
	ldi		iLoopRl, LOW(iVal)
	ldi		iLoopRh, HIGH(iVal)
iLoop:
	sbiw	iLoopRl, 1
	brne	iLoop

	dec		loopCt
	brne	delay10ms

	nop
	ret