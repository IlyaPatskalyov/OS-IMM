#include "video.h"

Video* getVideo(){
	return (Video*)0xA000;
}

extern "C" void intKeyboard(){
	char symbol;
	asm("in al,0x60\n");
	asm("mov byte ptr [ebp-0xd],al\n");
	Video * v = getVideo();
	v->put(symbol);
	asm("mov al, 0x20\n");
	asm("out 0x20, al\n");
	asm("leave\niret\n");
}

int main(void)
{
	Video * v = getVideo();
	v->init();
	v->clear();
	v->write("zzz");
}
