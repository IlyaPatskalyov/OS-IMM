PIC1			equ		0x20	; IO base address for master PIC
PIC1_COMMAND	equ		PIC1	; IO base address for slave PIC
PIC1_DATA		equ		PIC1+1

PIC2			equ		0xA0
PIC2_COMMAND	equ		PIC2
PIC2_DATA		equ		PIC2+1

PIC_START		equ		020h

ICW1_ICW4		equ		0x01	;  ICW4 (not) needed 
ICW1_SINGLE		equ		0x02	;  Single (cascade) mode 
ICW1_INTERVAL4	equ		0x04	;  Call address interval 4 (8)
ICW1_LEVEL		equ		0x08	;  Level triggered (edge) mode
ICW1_INIT		equ		0x10	;  Initialization - required!

ICW4_8086		equ		0x01	;  8086/88 (MCS-80/85) mode
ICW4_AUTO		equ		0x02	;  Auto (normal) EOI
ICW4_BUF_SLAVE	equ		0x08	;  Buffered mode/slave 
ICW4_BUF_MASTER	equ		0x0C	;  Buffered mode/master
ICW4_SFNM		equ		0x10	;  Special fully nested (not) 


PIC_Configure:
	push	ax
	; re-initialize interrupt #1 contoller

	mov	al, ICW1_INIT+ICW1_ICW4
	out	PIC1_COMMAND,al
	io_wait
	mov	al, ICW1_INIT+ICW1_ICW4
	out	PIC2_COMMAND,al
	io_wait

	
	mov	al, PIC_START
	out	PIC1_DATA, al
	io_wait
	mov	al, PIC_START+8
	out	PIC2_DATA, al
	io_wait

	mov	al, 4
	out	PIC1_DATA, al
	io_wait
	mov	al, 2
	out	PIC2_DATA, al
	io_wait

	
	mov	al, ICW4_8086
	out	PIC1_DATA, al
	io_wait
	mov	al, ICW4_8086
	out	PIC2_DATA, al
	io_wait
	
	mov	al,11111101b
	out	PIC1_DATA,al
	io_wait
	mov	al,0FFh
	out	PIC2_DATA,al
	io_wait

	pop	ax
	ret