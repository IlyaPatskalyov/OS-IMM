GDT_Table:
					gdt_record	0,0,0,0,0,0
	os_code_d		gdt_record	0xFFFF,	0x0000,	0x00,	10011000b,	00000000b, 0x00
	os_screen_d		gdt_record	0x1000,	0x8000,	0x0B,	10010010b,	00000000b, 0x00
	os_data_d		gdt_record	0xFFFF,	0x0000,	0x00,	10010010b,	00001111b, 0x00
	
GDT_Table_End:
GDT_Pointer:
	dw	GDT_Table_End-GDT_Table-1
	dw	GDT_Table
	dw	0
	
	
GDT_Selectors:
	os_code		equ	os_code_d   - GDT_Table
	os_data		equ	os_data_d   - GDT_Table
	os_screen	equ	os_screen_d - GDT_Table


