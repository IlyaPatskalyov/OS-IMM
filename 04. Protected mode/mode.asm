	org 7C00h
	; init registers
	cli
	xor	ax,ax
	mov	sp,ax
	mov	ss,ax
	mov	ds,ax
	mov	es,ax
	sti
	
	; create IDT Table
	mov	di,IDT_Table
	
	mov	ax,13
_c1:
	mov	si,IDT_Other
	mov	cx,8
	rep	movsb
	dec	ax
	cmp	ax,0
	jne	_c1

	mov	si,IDT_13
	mov	cx,8
	rep	movsb
	
	mov	ax,242
_c2:
	mov	si,IDT_Other
	mov	cx,8
	rep	movsb
	dec	ax
	cmp	ax,0
	jne	_c2

	; enter to protected mode
	cli
	lgdt	[GDT_Pointer]
	lidt	[IDT_Pointer]

	mov	eax,cr0
	or	al,1
	mov	cr0,eax
	sti
	
	jmp	1*8:run
run:
	int	13
	mov	ax,0BEAFh
	cli
	hlt

message		db	'int__'
Int_Other:
	mov	si,message
	jmp	Print
message_13	db	'int13'
Int_13:
	mov	si,message_13
Print:
	mov	ax,2*8
	mov	es,ax
	xor	di,di
	mov	ds,di
	mov	al,12
	mov	cx,5
_c3:
	movsb
	stosb
	loop	_c3
	iret

	
GDT_Pointer:
	dw	8*3-1
	dw	GDT_Table
	dw	0
GDT_Table:
	times   8 db 0
	db	0xFF,0xFF,	0x00,0x00,0x00,	10011000b,	00000000b, 0x00
	db	0x00,0x10,	0x00,0x80,0x0B,	10010010b,	00000000b, 0x00

IDT_Pointer:
	dw	256*8
	dw	IDT_Table
	dd	0
IDT_Sample:
IDT_13:
	dw	Int_13
	dw	8
	db	0, 10000110b, 0, 0
IDT_Other:
	dw	Int_Other
	dw	8
	db	0, 10000110b, 0, 0
IDT_Table:
	times	510 - ($ - $$) db 0
	db	055h
	db	0AAh