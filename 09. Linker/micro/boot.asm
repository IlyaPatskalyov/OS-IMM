[BITS 16]
global start
extern main
extern int_timer
extern intKeyboard
section .text

start:
;	org 7C00h
	; init registers
	cli
	xor	ax,ax
	mov	sp,ax
	mov	ss,ax
	mov	ds,ax
	mov	es,ax
	sti
	
	; load segments
	mov	ax,0211h
	mov	cx,0002h
	mov	dh,ch
	mov	bx,loadData
	int	13h
	
	cmp	ax,11h
	je	Kernel

	; boot failure
	mov	ah,0ah
	mov	al,'E'
	mov	bh,0
	mov	cx,1
	int	10h
	mov	ax,0DEADh
	
	cli
	hlt

	times	510 - ($ - $$) db 0
	db	055h
	db	0AAh
loadData:
%include "asm/macro.inc"
%include "asm/kernel.inc"
%include "asm/pic.inc"
%include "asm/int.inc"
%include "asm/gdt.inc"
%include "asm/idt.inc"
