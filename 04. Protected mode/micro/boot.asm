; http://stackoverflow.com/questions/282983/setting-up-irq-mapping
;%include "macroses.inc"
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
	;
	jmp Kernel
	cli
	hlt

	times	510 - ($ - $$) db 0
	db	055h
	db	0AAh
loadData:

%include "utils.inc"
%include "kernel.inc"
%include "int_other.inc"
%include "int_13.inc"
%include "gdt.inc"
%include "idt.inc"
