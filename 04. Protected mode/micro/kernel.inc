Kernel:
	; enter to protected mode
	cli
	lgdt	[GDT_Pointer]
	lidt	[IDT_Pointer]

	mov	eax,cr0
	or	al,1
	mov	cr0,eax
	

	mov	ax,3*8
	mov	ss,ax
	
	sti
	
	jmp	1*8:run
run:
	int	13
	
	cli
	hlt
