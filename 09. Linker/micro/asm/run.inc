extern	main
run:
	mov	ax, os_data
	mov	ss, ax
	mov	ds, ax
	mov	es, ax
	mov	ss, ax
	mov	fs, ax
	mov	gs, ax
	mov	sp, 0xFFFF

	sti
	call	main
	
	cli
	hlt

extern	int_c_keyboard
int_asm_keyboard:
	cli
	pusha
	call	int_c_keyboard
	popa
	sti
	iret


int_handler:
	iret