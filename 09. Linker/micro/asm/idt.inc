
IDT_Pointer:
	dw	IDT_Table_End - IDT_Table
	dw	IDT_Table
	dd	0

I_TRAP		equ	0x07
I_INT		equ	0x06
I_INT_32	equ	0x0E
I_DPL1		equ	0x20
I_DPL2		equ	0x40
I_DPL3		equ	0x60
I_PRESENT	equ	0x80

IDT_Table:
int00_d		idt_record	int_handler, os_code, I_TRAP
int01_d		idt_record	int_handler, os_code, I_TRAP
int02_d		idt_record	int_handler, os_code, I_TRAP
int03_d		idt_record	int_handler, os_code, I_TRAP
int04_d		idt_record	int_handler, os_code, I_TRAP
int05_d		idt_record	int_handler, os_code, I_TRAP
int06_d		idt_record	int_handler, os_code, I_TRAP
int07_d		idt_record	int_handler, os_code, I_TRAP
int08_d		idt_record	int_handler, os_code, I_TRAP
int09_d		idt_record	int_handler, os_code, I_TRAP
int0A_d		idt_record	int_handler, os_code, I_TRAP
int0B_d		idt_record	int_handler, os_code, I_TRAP
int0C_d		idt_record	int_handler, os_code, I_TRAP
int0D_d		idt_record	int_handler, os_code, I_TRAP
int0E_d		idt_record	int_handler, os_code, I_TRAP
int0F_d		idt_record	int_handler, os_code, I_TRAP

int10_d		idt_record	int_handler, os_code, I_TRAP
int11_d		idt_record	int_handler, os_code, I_TRAP
int12_d		idt_record	int_handler, os_code, I_TRAP
int13_d		idt_record	int_handler, os_code, I_TRAP
int14_d		idt_record	int_handler, os_code, I_TRAP
int15_d		idt_record	int_handler, os_code, I_TRAP
int16_d		idt_record	int_handler, os_code, I_TRAP
int17_d		idt_record	int_handler, os_code, I_TRAP
int18_d		idt_record	int_handler, os_code, I_TRAP
int19_d		idt_record	int_handler, os_code, I_TRAP
int1A_d		idt_record	int_handler, os_code, I_TRAP
int1B_d		idt_record	int_handler, os_code, I_TRAP
int1C_d		idt_record	int_handler, os_code, I_TRAP
int1D_d		idt_record	int_handler, os_code, I_TRAP
int1E_d		idt_record	int_handler, os_code, I_TRAP
int1F_d		idt_record	int_handler, os_code, I_TRAP

int20_d		idt_record	int_handler, os_code, I_TRAP	; IRQ 0 (Timer)
extern				int_keyboard
int21_d		idt_record	int_keyboard, os_code, I_INT_32+I_PRESENT	; IRQ 1	(Keyboard)
int22_d		idt_record	int_handler, os_code, I_TRAP	; IRQ 2
int23_d		idt_record	int_handler, os_code, I_TRAP	; IRQ 3
int24_d		idt_record	int_handler, os_code, I_TRAP	; IRQ 4
int25_d		idt_record	int_handler, os_code, I_TRAP	; IRQ 5
int26_d		idt_record	int_handler, os_code, I_TRAP	; IRQ 6 (FDC)

IDT_Table_Other:
%rep 256 - (IDT_Table_Other-IDT_Table)/8
		idt_record	int_handler, os_code, I_TRAP
%endrep
IDT_Table_End:
