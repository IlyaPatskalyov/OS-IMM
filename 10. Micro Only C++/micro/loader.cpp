#include "base.h"
#include "kernel.h"
#include "gdt.h"
asm(".code16gcc\n");

GDT_Entry gdt[] = {
    { 0, },
    BUILD_GDT_ENTRY(0, 0xffffffff, GDT_CS_TYPE),
    BUILD_GDT_ENTRY(0, 0xffffffff, GDT_DS_TYPE)
};
GDT_Pointer gdt_pointer;

__attribute__ ((section (".loader")))
int main() 
{
	cli();
	setSegmentRegisters(0x0);
	sti();
	
	readFromDevice(0x0214, 0x7e00, 0x2, 0x0);
	
	gdt_pointer.size = sizeof(GDT_Entry)*3-1;
	gdt_pointer.offset = (unsigned long)gdt;
	asm("lgdt %0" : "=m" (gdt_pointer));

	asm("mov	%cr0,%eax\n");
	asm("or	$1,%eax\n");
	asm("mov	%eax,%cr0\n");
	
	asm("jmp $0x8,$0x7e00");
}

