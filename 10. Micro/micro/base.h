#ifndef __BASE_H__
#define __BASE_H__

#define iret() asm("leave\niret")

inline static void io_wait(){
	asm ("jmp $+2");
}

inline static void sti()
{
	asm("sti");
}

inline static void cli()
{
	asm("cli");
}

inline static void halt()
{
	asm("hlt");
}

inline static unsigned char inb(unsigned short port){
	unsigned char ret;
	asm  ("inb al, dx\n" : "=a" (ret) : "d" (port));
	return ret;
}

inline static void outb(int port, unsigned char data)
{
	asm volatile ( "outb dx, al\n":: "a" (data), "d" (port)	);
}


#endif
