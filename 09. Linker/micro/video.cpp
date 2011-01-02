#include "video.h"

void Video::init()
{
    pos = 0;
    off = 0;
    mem = (unsigned short*)0xB8000;
}

void Video::clear(){
    for(int i = 0; i <(80*25); i++) {
	mem[i] = (unsigned char)' ' | 0x0700;
    }
    pos = 0;
    off = 0;
}

void Video::write(char *cp){
    char *str = cp, *ch;
    for(ch = str; *ch; ch++){
	put(*ch);
    }
}

void Video::put(char c){
    if(pos >= 80 || c == 0x1C)
    {
	pos = 0;
	off += 80;
    }
    if (off >= (80*25)){
	nextline();
    }
    if (c == 0x1C)
	return;
    mem[off+pos] = (unsigned char) c | 0x0700;
    pos++;
}

void Video::nextline(){
	for(int i = 0; i < (80*24); i++) 
		mem[i] = mem[i+80];
	for(int i = 0; i < 80; i++)
		mem[80*24+i] = 0x0700;
	pos = 0;
	off -= 80;
}
