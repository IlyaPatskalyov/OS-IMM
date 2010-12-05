Int_Timer_Message	db	'timer'
Int_Timer:
	pusha
	mov	si,Int_Timer_Message
	mov	cx,5
;	call	PrintString
	popa
	iret
