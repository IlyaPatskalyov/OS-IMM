#include "base.h"
#include "interrupt.h"

extern void default_handler();

void Interrupt::init(){
	cli();
	for (int i = 0 ;i<256;i++)
		set(i, default_handler, TRAP_GATE|BITS_32|ABSENT|RING_0);

	pointer.size=(256*8)-1;
	pointer.offset=(unsigned long)idt;
	
	asm("lidt %0" : "=m" (pointer));
	pic_mask = 0xFFFF;
	picInit();
	sti();
}


void Interrupt::set(int id, void (*pointer)(), unsigned char control)
{
	union
	{
		void (*function)();
		struct addr function_addr;
	} interrupt;

	interrupt.function = pointer;
	idt[id].selector = 0x8;
	idt[id].dword_count = 0;
	idt[id].type = control;
	idt[id].offset1 = interrupt.function_addr.offset;
	idt[id].offset2 = interrupt.function_addr.base;
}

void Interrupt::picInit()
{
	outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
	io_wait();
	
	outb(PIC1_DATA, PIC1_VEC);                 // define the PIC vectors
	io_wait();
	outb(PIC2_DATA, PIC2_VEC);
	io_wait();
	
	outb(PIC1_DATA, 4);                       // continue initialization sequence
	io_wait();
	outb(PIC2_DATA, 2);
	io_wait();
 
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	picSetMask();
}

void Interrupt::picSetMask(){
	outb(PIC1_DATA, pic_mask & 0xff);
	io_wait();
	outb(PIC2_DATA, (pic_mask >> 8) & 0xff);
	io_wait();
}

void Interrupt::enableIrq(unsigned short x, void (*handler)(), unsigned char control){
	pic_mask &= ~(1<<x);
	if (x>=8){
		pic_mask &= ~(1<<2);
		set(x + PIC2_VEC - 8, handler, control);
	}
	else
		set(x + PIC1_VEC, handler, control);
	picSetMask();
}

void Interrupt::disableIrq(unsigned short x){
	pic_mask |= (1 << x);
	if(x >= 8){
		pic_mask |= (1 << 2);
		set(x + PIC2_VEC - 8, default_handler, INT_GATE|BITS_32|ABSENT|RING_3);
	}
	else
		set(x + PIC1_VEC, default_handler, INT_GATE|BITS_32|ABSENT|RING_3);
	picSetMask();
}
