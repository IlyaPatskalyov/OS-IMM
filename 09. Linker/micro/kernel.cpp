#include "video.h"


extern "C" void int_timer(){
	Video v;
	v.write("Hello, world!");
	asm("leave\niret\n");
}

int main(void)
{
	Video v;
	v.clear();
	v.write("zzz");
}
