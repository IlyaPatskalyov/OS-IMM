#include "video.h"
#include "base.h"

Video* getVideo(){
	return (Video*)0xA000;
}


extern "C" void int_Keyboard(){
	char symbol = Base::inport(0x60);
	Video * v = getVideo();
	v->put(symbol);
	Base::outport(0x20, 0x20);
	asm("leave\niret\n");
}

int main(void)
{
	Video * v = getVideo();
	v->init();
	v->clear();
	v->write("zzz");
	for(;;);
}
