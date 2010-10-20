	org 	7c00h
	xor	ax,ax
	cli
	mov	ds,ax
	mov	ss,ax
	mov	es,ax
	sti
	mov	ax,0201h
	mov	cx,2
	mov	dh,0
	mov	bx,run
	int	13h
	
	cmp	ax,1
	jne	fail
	
	jmp	run

fail:
	cli
	hlt
	times	510 - ($ - $$) db 0
	db	055h
	db	0AAh
run:
	inc	byte [cs:count]
	mov	ax,[cs:count]
	cli
	hlt
count	dw	02h
	times	1024	db	0DDh