#include "video.h"
#include "keyboard.h"
#include "base.h"
#include "interrupt.h"

char * mess = "Micro OS\n\n";
Video v;
Keyboard k;
Interrupt i;

extern void int_keyboard(){
	cli();
	k.interrupt();
	sti();
	asm("leave");
	asm("iret");
}

extern void default_handler(){
	cli();
	v.write("default");
	sti();
	asm("leave");
	asm("iret");
}


int main(void)
{
	i.init();
	i.enableIrq(1, int_keyboard, INT_GATE|BITS_32|PRESENT|RING_0);

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
