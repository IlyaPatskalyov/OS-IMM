Int_Keyb_Message	db	'keyb'
Int_Keyb:
	pusha
	mov	si,Int_Keyb_Message
	mov	cx,5
	call	PrintString
	popa
	iret
