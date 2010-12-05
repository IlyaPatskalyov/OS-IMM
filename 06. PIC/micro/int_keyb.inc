Int_Keyb_Message	db	'keyb'
Int_Keyb:
	cli
	hlt
	pusha
	mov	si,Int_Keyb_Message
	mov	cx,4
	call	PrintString
	popa
	iret
