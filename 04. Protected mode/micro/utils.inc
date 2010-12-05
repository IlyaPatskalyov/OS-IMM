PrintString:
	pusha
	mov	ax,2*8
	mov	es,ax
	xor	di,di
	mov	ds,di
	mov	al,12
PrintString_loop:
	movsb
	stosb
	loop	PrintString_loop
	popa
	ret
