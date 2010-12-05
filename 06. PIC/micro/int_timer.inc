Int_Timer_Message	db	't'
Int_Timer:
	pusha
	mov	si,Int_Timer_Message
	mov	cx,1
	call	PrintString
	popa
	iret
