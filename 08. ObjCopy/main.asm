;BITS 32 ; “ут
global _start
;section .text ;
_start:
	mov		eax,1
    int		0x80
    ret