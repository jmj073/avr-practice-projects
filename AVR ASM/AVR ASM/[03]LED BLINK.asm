.include "m128adef.inc"

.def mask		= r16
.def ledR		= r17
.def oLoopR		= r18
.def iLoopRl	= r24
.def iLoopRh	= r25

.equ oVal		= 71
.equ iVal		= 28168

.cseg
.org	0x0000

	clr		ledR
	ldi		mask,		(1 << PINB0)
	out		DDRB,		mask

start:
	eor		ledR,		mask
	out		PORTB,		ledR

	ldi		oLoopR,		oVal

oLoop:
	ldi		iLoopRl,	LOW(iVal)
	ldi		iLoopRh,	HIGH(iVal)

iLoop:
	sbiw	iLoopRl,	1
	brne	iLoop
	
	dec		oLoopR
	brne	oLoop

	rjmp	start