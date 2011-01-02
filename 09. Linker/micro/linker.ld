OUTPUT_FORMAT("binary")
ENTRY (start)
SECTIONS{
	. = 0x7C00;
	.text . :  {
		code = .;
		*(.text)
		. = ALIGN(0x200);
	}
	
	.data 0xA000 : {
		data = .;
		*(.data)
		. = ALIGN(0x200);
	}
	
	.rodata . : {
		rodata = .;
		*(.rodata)
		. = ALIGN(0x200);
	}
	
	.bss : {
		sbss = .;
		*(COMMON)
		*(.bss)
		ebss = .;
	}
	end = .;
}
