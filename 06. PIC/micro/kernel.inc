Kernel:
	; enter to protected mode
	cli
	lgdt	[GDT_Pointer]
	lidt	[IDT_Pointer]

	mov	eax,cr0
	or	al,1
	mov	cr0,eax
	

	mov	ax,os_data
	mov	ss,ax
	
	call	PIC_Configure
	
	sti
	
	
	jmp	os_code:run
run:
	jmp	run
;	int	13

	cli
	hlt
