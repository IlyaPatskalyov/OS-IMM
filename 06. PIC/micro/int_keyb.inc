Int_Keyb_Message	db	20
Int_Keyb:
	pusha
	in al, 60h
	mov	byte [Int_Keyb_Message],al
	mov al, 20h
	out 20h, al
	mov	si,Int_Keyb_Message
	mov	cx,1
	call	PrintString
	popa
	iret
