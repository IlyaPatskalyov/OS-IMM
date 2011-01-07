#ifndef __BASE_H__
#define __BASE_H__

inline static void io_wait(){
	asm ("jmp 1f;1:jmp 1f;1:");
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
	asm  ("inb %%dx, %%al\n" : "=a" (ret) : "d" (port));
	return ret;
}

inline static void outb(int port, unsigned char data)
{
	asm volatile ( "out %%al, %%dx\n":: "a" (data), "d" (port)	);
}

#endif
