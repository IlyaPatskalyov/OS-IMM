OUTPUT_FORMAT("binary")
ENTRY (start)
SECTIONS{
	. = 0x7C00;
	.text . :  {
		code = .;
		data = .;
		*(.text)
		. = ALIGN(256);
	}
}
