/*.include "m128adef.inc"
.include "util.inc"

.dseg
var: .byte 1


.cseg
.org	0x0000

	setStack RAMEND, r16

	ldi r16, 0x01

	dec r16

 	ldi		r16,	0x12
	out		PORTB,	r16

	in		r0,		PORTB			; access by I/O register address
	lds		r1,		(PORTB + 0x20)	; access by data memory address

	lds		r2,		16

	ldi		XL,		LOW(var)
	ldi		XH,		HIGH(var)
	ldi		r16,	0x34

	st		X,		r16
	ld		r0,		X

	st		X+,		r20

	std		Y+4,	r1*/