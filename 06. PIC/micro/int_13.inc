Int_13_Message	db	'int13    '
Int_13:
	pusha
	mov	si,Int_13_Message
	mov	cx,5
	call	PrintString
	popa
	iret
