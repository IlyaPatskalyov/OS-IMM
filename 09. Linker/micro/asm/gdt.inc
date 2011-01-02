bits 32
GDT_Table:
			gdt_record	0,	0,	0,	0,		0,		0
	os_code_d	gdt_record	0xFFFF,	0x0000,	0x00,	10011010b,	11001111b,	0x00
	os_data_d	gdt_record	0xFFFF,	0x0000,	0x00,	10010010b,	11001111b,	0x00
	
GDT_Table_End:
GDT_Pointer:
	dw	GDT_Table_End-GDT_Table-1
	dw	GDT_Table
	dw	0
	
	
GDT_Selectors:
	os_code		equ	os_code_d   - GDT_Table
	os_data		equ	os_data_d   - GDT_Table
