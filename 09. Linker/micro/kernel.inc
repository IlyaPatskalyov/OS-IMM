Kernel:
	; enter to protected mode
	cli
	lgdt	[GDT_Pointer]
	lidt	[IDT_Pointer]

	mov	eax,cr0
	or	al,1
	mov	cr0,eax
	
	mov	ax,os_data
	mov	ss, ax
	mov	ds, ax
	mov	es, ax
	mov	ss, ax
	mov	fs, ax
	mov	gs, ax
	mov	sp, 0xFFFF

;	call	PIC_Configure
	sti
	
	jmp	os_code:run
[BITS 32]
run:
	call	main

	cli
	hlt
