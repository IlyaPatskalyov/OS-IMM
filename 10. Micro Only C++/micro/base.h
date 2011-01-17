#ifndef __BASE_H__
#define __BASE_H__

inline static __attribute__ ((always_inline))
void iret() 
{
	asm("leave\niret");
}

inline static __attribute__ ((always_inline))
void sti()
{
	asm("sti");
}

inline static __attribute__ ((always_inline))
void cli()
{
	asm("cli");
}

inline static __attribute__ ((always_inline))
void halt()
{
	asm("hlt");
}


inline static __attribute__ ((always_inline)) void io_wait(){
	asm ("jmp 1f;1:jmp 1f;1:");
}

inline static __attribute__ ((always_inline))
unsigned char inb(unsigned short port){
	unsigned char ret;
	asm  ("inb %%dx, %%al\n" : "=a" (ret) : "d" (port));
	return ret;
}

inline static __attribute__ ((always_inline)) 
void outb(int port, unsigned char data){
	asm volatile ( "out %%al, %%dx\n":: "a" (data), "d" (port)	);
}

inline static __attribute__ ((always_inline)) 
void readFromDevice(unsigned short ax, unsigned short bx, unsigned short cx, unsigned short dx)
{
	asm ( "int $0x13\n" :: "ax" (ax), "b" (bx), "cx" (cx), "dx" (dx) );
}

inline static __attribute__ ((always_inline)) 
void setSegmentRegisters(unsigned short segment){
	asm("nop" :: "ax" (segment) );
	asm("mov %ax, %es\nmov %ax, %fs\nmov %ax, %gs\nmov %ax, %ss\n");
}
#endif
