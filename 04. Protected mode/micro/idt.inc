IDT_Pointer:
	dw	256*8
	dw	IDT_Table
	dd	0
IDT_Table:
%rep 13
	dw Int_Other
	dw 8
	db 0, 10000110b, 0, 0
%endrep
		dw Int_13
		dw 8
		db 0, 10000110b, 0, 0
%rep 256 - 14
	dw Int_Other
	dw 8
	db 0, 10000110b, 0, 0
%endrep
