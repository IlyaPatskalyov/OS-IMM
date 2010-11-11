	org 	7c00h
	xor	ax,ax
	cli
	xor	ax,ax
	mov	ds,ax
	mov	ss,ax
	mov	es,ax
	sti
	mov	ax,0203h
	mov	cx,2
	mov	dh,0
	mov	bx,zz
	int	13h
	cmp	ah,0
	je	zz

	cli
	hlt

print:
	mov	ah,0Ah
	mov	al,48h
	mov	bl,0
	mov	cx,1
	int	10h
	ret
	times	510 - ($ - $$) db 0
	db	055h
	db	0AAh
zz:
	jmp	start
count2	dw 	0
int8:
	push	ax
	inc	byte [cs:count]
	mov	ah,[cs:speed]
	cmp	ah,15
	jg	frj8
	cmp	[cs:count],ah
	jle	frj8
	mov	byte [cs:count],0
	mov	byte [cs:flg_p],1
frj8:	pop	ax
	db	0eah
addr8	dw	0,0

int9:
	push	ax
	push	bx
	push	si
	in	al,60h
	mov	bl,al
	xor	bh,bh
	mov	si,keys
	mov	cx,0
kLoop:
	lodsb
	cmp	al,bl
	je	kPush
	cmp	al,0
	je	kFinish
	inc	bh
	jmp	kLoop
kPush:
	mov	si,[cs:kHead]
	inc	si
	cmp	si,10
	jne	_kPush
	mov	si,0
_kPush:
	mov	[cs:kBuffer+si],bh
	mov	[cs:kHead],si
kFinish:
	mov	al,20h
	out	20h,al
	pop	si
	pop	bx
	pop	ax
	iret
frj9:	db	0eah
addr9	dw	0,0

start:
	xor	ax, ax
	push	ax
	pop	ds

	mov	si, 08h*4
	mov 	di, addr8
	mov	cx,4
	rep	movsb

	mov	si, 09h*4
	mov 	di, addr9
	mov	cx,4
	rep	movsb

	push	ss
	pop	ds

	cli
	xor	ax,ax
	push	ax
	pop	es
	mov	di,08h*4
	mov	ax, int8
	stosw
	mov	ax,ss
	stosw

	mov	di,09h*4
	mov	ax, int9
	stosw
	mov	ax,ss
	stosw

	sti
	
	xor	ax,ax
	push	ax
	pop	es
	mov	bh,[es:449h]
	mov	bl,[es:462h]
	mov	ax,[es:44ch]
	mov	cx,bx
	xor	ch,ch
	shr	ax,4
	mul	cx
	mov	di,0b000h
	cmp	bh,7
	jge	_2
	mov	di,0b800h
	cmp	bh,3
	jbe	_2
_2:
	add	di,ax
	mov	dh,[es:44Ah]
	shl	dh,1
	mov	dl,[es:484h]
	inc	dl
	xor	bh,bh
	mov	bl,dh
	push	di
	pop	es
	

; clear screen
	xor	di,di
	mov	ax,bx
	mul	dl
	shr	ax,1
	mov	cx,ax
	mov	ax,00000h
	rep	stosw

	xor	di,di
	mov	cx,bx
	shr	cx,1
	mov	ax,0c020h
	rep	stosw

	mov	cx,[head]
	shr	cx,1
	mov	ax,03020h
initPrintSnake:
	mov	si,cx
	add	si,cx
	mov	di,[queue+si]
	stosw
	loop	initPrintSnake

	xor	di,di
	jmp	cycle

keys	db	35h,2Ch,28h,1Eh,01h,48h,50h,4Bh,4Dh,39h,13h,0
keyJump dw	kSpeedUp
	dw	kSpeedDown
	dw	kLengthUp
	dw	kLengthDown
	dw	kEsc
	dw	kUp
	dw	kDown
	dw	kLeft
	dw	kRight
	dw	kStop
	dw	kReverse
kBuffer	times 16 db	0
kHead	dw	0
kTail	dw	0

kSpeedUp:
	cmp	byte [speed],0
	je	_kSpeedUp
	dec	byte [speed]
_kSpeedUp:
	jmp	cycle
kSpeedDown:
	cmp	byte [speed],15
	jg	_kSpeedDown
	inc	byte [speed]
_kSpeedDown:
	jmp	cycle
kLengthUp:
	or	byte [flgL],10b
	jmp	cycle
kLengthDown:
	cmp	word [len],0
	jl	_kLengthDown
	or	byte [flgL],1b
_kLengthDown:
	jmp	cycle
kEsc:	
	jmp	exit
kUp:	
	cmp	word [aspect],2
	jne	_kUp
	xor	byte [reverse],1
_kUp:
	mov	word [aspect],1
	mov	byte [flg_s],0
	jmp	cycle
kDown:	
	cmp	word [aspect],1
	jne	_kDown
	xor	byte [reverse],1
_kDown:
	mov	word [aspect],2
	mov	byte [flg_s],0
	jmp	cycle
kLeft:
	cmp	word [aspect],3
	jne	_kLeft
	xor	byte [reverse],1
_kLeft:
	mov	word [aspect],0
	mov	byte [flg_s],0
	jmp	cycle
kRight:
	cmp	word [aspect],0
	jne	_kRight
	xor	byte [reverse],1
_kRight:
	mov	word [aspect],3
	mov	byte [flg_s],0
	jmp	cycle
kStop:
	xor	byte [flg_s],1
	jmp	cycle
kReverse:
	xor	byte [reverse],1
	jmp	cycle

processKeyBuffer:
	mov	si,[kTail]
	inc	si
	cmp	si,10
	jne	_pKB
	mov	si,0
_pKB:
	mov	al,[kBuffer+si]
	shl	al,1
	mov	[kTail],si
	mov	si,ax
	jmp	[keyJump+si]
	
cycle:
	mov	ax,[kHead]
	cmp	ax,[kTail]
	jne	processKeyBuffer

	cmp	byte [flg_p],1
	je	printSnake
	jmp	cycle

exit:
	cli
	xor	cx,cx
	push 	cx
	pop	es
	mov	di,08h*4
	mov	ax,[addr8]
	stosw
	mov	ax,[addr8+2]
	stosw

	mov	di,09h*4
	mov	ax,[addr9]
	stosw
	mov	ax,[addr9+2]
	stosw
	sti
;
	mov	ax,0003h
	int	10h
	cli
	hlt

printSnake:
	cmp	byte [reverse],1
	jne	_printSnake
	push	word [head]
	push	word [tail]
	pop	word [head]
	pop	word [tail]
	not	word [delta]
	inc	word [delta]

_printSnake:
	mov	byte[flg_p],0
	mov	si,[head]
	mov	di,[queue+si]
	mov	si,[aspect]
	shl	si,1
	mov	cx,di
	jmp	[aspjump+si]
actionUp:
	sub	di,bx
	cmp	di,bx
	jg	printEnd
	mov	word [aspect],3
	jmp	printSnake

actionDown:
	add	di,bx
	mov	ax,bx
	mul	dl
	cmp	di,ax
	jle	printEnd
	sub	di,ax
	add	di,bx
	jmp	printEnd

actionLeft:
	cmp	di,0
	jne	_actionLeft
	mov	di,bx
	sub	di,2
	jmp	printEnd
_actionLeft:
	sub	di,2
	mov	ax,di
	div	dh
	cmp	ah,9Eh
	jne	printEnd
	xor	ah,ah
	add	al,2
	mul	dh
	mov	di,ax
	sub	di,2
	jmp	printEnd

actionRight:
	add	di,2
	mov	ax,di
	div	dh
	cmp	ah,0
	jne	printEnd
	xor	ah,ah
	dec	al
	mul	dh
	mov	di,ax
	jmp	printEnd

cmpSiDelta:
	cmp word [delta],0
	jl	deltaTest
	cmp	si,32000
	jne	_cmpSiDelta
	mov	si,0
	jmp	cx
deltaTest:
	cmp	si,0
	jne	_cmpSiDelta
	mov	si,32000
_cmpSiDelta:
	jmp	cx


printEnd:
	mov	byte [reverse],0
	mov	al,[flgL]
	test	al,10b
	jnz	_9
	test	al,01b
	jnz	printState2
	cmp	byte [flg_s],1
	je	printState2

_9:
	mov	si,[head]
	add	si,[delta]

	mov	cx, _4
	jmp	cmpSiDelta
_4:

	mov	[queue+si],di
	mov	[head],si


	mov	ah,30h
	mov	al,20h
	mov	cx,[es:di]
	and	ch,0Fh
	cmp	cl,20h
	jne	_6
	add	ah,ch
	inc	ah
_6:	stosw
	inc	word [len]

	test 	byte [flgL],10b
	jnz	printToCycle
printState2:
	test	byte [flgL],01b
	jnz	_9a
	cmp	byte [flg_s],1
	je	printToCycle

_9a:	mov	si,[tail]
	mov	di,[queue+si]
	add	si,[delta]

	mov	cx,_4a
	jmp	cmpSiDelta
_4a:
	mov	[tail],si
	mov	ax,[es:di]
	mov	cx,ax
	and	ch,0Fh
	cmp	ch,0
	je	_7
	dec	ah
	stosw	
	dec	word [len]
	jmp	printToCycle

_7:	mov	ah,000h
	mov	al,00h
	stosw
	dec	word [len]
	jmp	printToCycle

printToCycle:
	test	byte [flgL],11b
	mov	byte [flgL],0
	jz	_8
	mov	byte [flg_p],1
_8:	jmp 	cycle

speed	db	5
len 	dw	1
count	db	0
flg_s	db	0
flgL	db	0
flg_p	db	0
reverse	db	0
delta	dw	2
aspect	dw	2
aspjump	dw	actionLeft, actionUp, actionDown, actionRight
head	dw	4
tail	dw	0
queue	dw	10+160,8+160,6+160
;	times 512*3 - ($ - $$) db 0
	times 1474560 - ($ - $$) db 0
;	times 32000 dw 0
