bits 16
global start
start:
	; init registers
	cli
	xor	ax,ax
	mov	ds,ax
	sti
	
	; load segments
	mov	ax,0214h
	mov	cx,0002h
	mov	dh,ch
	mov	bx,run
	int	13h
	
	cmp	ax,14h
	jne	error

	cli
	lgdt	[GDT_Pointer]

	mov	eax,cr0
	or	al,1
	mov	cr0,eax
	
	mov	ax, 0x10
	mov	ss, ax
	mov	ds, ax
	mov	es, ax
	mov	ss, ax
	mov	fs, ax
	mov	gs, ax
	mov	sp, 0xFFFF

	sti
	jmp	0x08:run

error:
	; boot failure
	mov	eax, 0xB8000
	mov	word [eax], 0xC45

	cli
	hlt

GDT_Table:
	db	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	db	0xFF,0xFF,0x00,0x00,0x00,0x9A,0xCF,0x00
	db	0xFF,0xFF,0x00,0x00,0x00,0x92,0xCF,0x00
GDT_Pointer:
	dw	GDT_Pointer-GDT_Table-1
	dw	GDT_Table
	dw	0


	times	510 - ($ - $$) db 0
	db	055h
	db	0AAh
bits 32
extern	main
run:
	call	main
