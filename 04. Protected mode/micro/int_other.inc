message		db	'int__'
Int_Other:
	pusha
	mov	cx,5
	mov	si,message
	call	PrintString
	popa
	iret
