#include "base.h"

unsigned char Base::inport(unsigned short port){
	unsigned char ret;
	asm  ("in al, dx\n" : "=a" (ret) : "d" (port));
	return ret;
}

void Base::outport(int port, unsigned char data)
{
	asm volatile ( "outb dx, al\n":: "a" (data), "d" (port)	);
}

