OUTPUT_FORMAT("binary")
ENTRY (start)
SECTIONS{
	. = 0x7C00;
	.text . :  {
		code = .;
		*(.text)
		. = ALIGN(0x1000);
	}
	
	.data 0x9000 : {
		data = .;
		*(.data)
		. = ALIGN(0x1000);
	}
	
	.rodata . : {
		rodata = .;
		*(.rodata)
		. = ALIGN(4096);
	}
	
	.bss : {
		sbss = .;
		*(COMMON)
		*(.bss)
		ebss = .;
	}
	end = .;
}
