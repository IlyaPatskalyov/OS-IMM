OUTPUT_FORMAT("binary")
ENTRY (main)
SECTIONS{
	.loader 0x7c00 : {
		code = .;
		*(.loader)
		. = ALIGN(0x200);
	}
	.text 0x7E00 :  {
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
