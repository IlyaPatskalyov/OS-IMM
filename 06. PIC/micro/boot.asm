
	org 7C00h
	; init registers
	cli
	xor	ax,ax
	mov	sp,ax
	mov	ss,ax
	mov	ds,ax
	mov	es,ax
	sti
	
	; load segments
	mov	ax,0205h
	mov	cx,0002h
	mov	dh,ch
	mov	bx,loadData
	int	13h
	
	cmp	ax,5
	je	Kernel

	; boot failure
	mov	ah,0ah
	mov	al,'E'
	mov	bh,0
	mov	cx,1
	int	10h
	
	cli
	hlt

	times	510 - ($ - $$) db 0
	db	055h
	db	0AAh
loadData:
%include "macro.inc"
%include "utils.inc"
%include "kernel.inc"
%include "pic.inc"
%include "int_other.inc"
%include "int_13.inc"
%include "int_timer.inc"
%include "int_keyb.inc"
%include "gdt.inc"
%include "idt.inc"
