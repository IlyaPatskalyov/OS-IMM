%include "asm/macro.inc"

global start
start:
	; init registers
	cli
	xor	ax,ax
	mov	sp,ax
	mov	ss,ax
	mov	ds,ax
	mov	es,ax
	sti
	
	; load segments
	mov	ax,0214h
	mov	cx,0002h
	mov	dh,ch
	mov	bx,init
	int	13h
	
	cmp	ax,14h
	je	init

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
init:
	cli
	lgdt	[GDT_Pointer]

	mov	eax,cr0
	or	al,1
	mov	cr0,eax
	
	mov	ax, os_data
	mov	ss, ax
	mov	ds, ax
	mov	es, ax
	mov	ss, ax
	mov	fs, ax
	mov	gs, ax
	mov	sp, 0xFFFF

	sti
	
	jmp	os_code:run

%include "asm/gdt.inc"
%include "asm/run.inc"
