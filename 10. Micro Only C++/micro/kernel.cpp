#include "base.h"
#include "kernel.h"
#include "video.h"
#include "keyboard.h"
#include "interrupt.h"

char * mess = "Micro OS\n\n";
Video v;
Keyboard k;
Interrupt i;

extern void int_keyboard();
extern void default_handler();

void kernel()
{
	setSegmentRegisters(0x10);
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

extern void int_keyboard()
{
	cli();
	k.interrupt();
	sti();
	iret();
}

extern void default_handler(){
	cli();
	outb(0x20, 0x20);
	v.put('z');
	sti();
	iret();
}

