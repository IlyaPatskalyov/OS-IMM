#include "video.h"
#include "base.h"
#include "pic.h"

inline static Video* getVideo(){
	return (Video*)0xA000;
}

extern "C" void int_Keyboard(){
	char symbol = inb(0x60);
	outb(0x20, 0x20);

	Video * v = getVideo();
	v->put(symbol);
	asm("leave");
	asm("iret");
}
int main(void)
{
	init_pic();
	
	Video * v = getVideo();
	v->init();
	v->clear();
	v->write("zzz");
	for(;;);
}
