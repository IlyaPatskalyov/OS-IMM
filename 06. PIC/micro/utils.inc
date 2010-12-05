PrintString:
	pusha
	mov	ax,os_screen
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
