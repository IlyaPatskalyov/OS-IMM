#include "video.h"
#include "keyboard.h"
#include "base.h"
#include "pic.h"

char * mess = "Micro OS\n\n";
Video v;
Keyboard k;

extern "C" void int_keyboard(){
	cli();
	k.interrupt();
	sti();
	asm("leave");
	asm("iret");
}

int main(void)
{
	init_pic();
	k.init();
	v.init();
	v.clear();
	v.write(mess);
	for(;;){
		cli();
		while (!k.isEmpty()){
			v.put(k.get());
		}
		sti();
	}
}
