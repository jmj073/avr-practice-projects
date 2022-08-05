;.include "m128adef.inc"
;.include "util.inc"
;
;.def tmp		= r16
;.def loopCnt	= r17
;
;.equ arrSize	= 10
;
;.dseg
;.org SRAM_START
;darr: .byte 10
;
;
;.cseg
;.org	0x0000
;
;	setStack RAMEND, r16
;
;/*	ldi r16, RAMPZ
;
;	cpi r16, 0x30*/
;
;	ldi r16, 0x12
;	sts RAMPZ, r16
;	ldi r16, 0x34
;	/*sts (ZL + 0x20), r16*/
;
;
;
;	ldi		XL,			LOW(darr)
;	ldi		XH,			HIGH(darr)
;
;	ldi		ZL,			LOW(carr * 2)
;	ldi		ZH,			HIGH(carr * 2)
;
;	ldi		loopCnt,	arrSize	
;
;loop:
;	lpm		tmp,	Z+
;	st		X+,		tmp
;
;	dec		loopCnt
;	brne	loop
;
;forever:
;	rjmp	forever
;
;
;carr:
;	.db	1, 2, 3, 4, 5, 6, 7, 8, 9, 10