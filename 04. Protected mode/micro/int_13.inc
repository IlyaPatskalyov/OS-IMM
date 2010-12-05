message_13	db	'int13'
Int_13:
	pusha
	mov	si,message_13
	mov	cx,5
	call	PrintString
	popa
	iret
