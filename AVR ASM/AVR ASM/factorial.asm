/*.include "m128adef.inc"
.include "util.inc"

.def arg = r0
.def a = r1


.cseg
.org	0x0000

	setStack RAMEND, r16

	ldi		r16,	6
	mov		r0,		r16
	
	rcall	factorial

loop:
	rjmp	loop



factorial: ; arg: r0 ; r0 <= 6
	tst		r0
	brne	if_not_zero

	inc		r0				; 0 -> 1
	ret
if_not_zero:
	push	r0
	dec		r0
	rcall	factorial
	pop		r2
	mul		r0,		r2

	ret


sum:
	tst		arg
	breq	sum_end

	push	arg
	dec		arg
	rcall	sum
	pop		a
	add		arg, a
sum_end:
	ret


*/