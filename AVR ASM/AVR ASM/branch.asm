 .include "m128adef.inc"

	.cseg
	.org 	0x00

 	ldi r16, 0xFF
	inc r16 ; 'inc' instruction�� carry flag�� ������ ���� �ʴ� �� �ϴ�
/*	ldi r17, 0x01
	add r16, r17*/

	brcs skip 
	; if carry cleared
	ldi r16, 0x01
	out DDRB, r16
	out PORTB, r16