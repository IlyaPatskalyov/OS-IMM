Kernel:
	; enter to protected mode
	cli
	
	call	PIC_Configure

	lgdt	[GDT_Pointer]
	lidt	[IDT_Pointer]

	mov	eax,cr0
	or	al,1
	mov	cr0,eax
	
	mov	ax,os_data
	mov	ss,ax
	
	sti
	
	jmp	os_code:run
run:
	jmp	run

	cli
	hlt
