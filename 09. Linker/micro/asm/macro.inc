%macro gdt_record 6
	dw	%1		; limit [15..0]
	dw	%2		; base  [15..0]
	db	%3		; base  [23..16]
	db	%4		; P-DPL-1-1-C-R-A
	db	%5		; G-D-0-AVL-limit [19..16]
	db	%6		; base  [31..24]
%endmacro

%macro idt_record 3
	dw	%1, %2
	db	0, %3
	dw	0
%endmacro

bits 16
