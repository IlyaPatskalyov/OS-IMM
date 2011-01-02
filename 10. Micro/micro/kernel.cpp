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
	outb(0x20, 0x20);
	v.put('z');
	sti();
	asm("leave");
	asm("iret");
}


int main(void)
{
	i.init();
	k.init();
	v.init();
	v.clear();
	v.write(mess);
	
	i.enableIrq(1, int_keyboard, INT_GATE|BITS_32|PRESENT|RING_0);
	i.enableIrq(0, default_handler, INT_GATE|BITS_32|PRESENT|RING_0);

	for(;;){
		cli();
		while (!k.isEmpty()){
			v.put(k.get());
		}
		sti();
	}
}
