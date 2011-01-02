#include "video.h"

Video::Video()
{
    pos = 0;
    off = 0;
    mem = (unsigned short*)0xB8000;
}
Video::~Video(){}

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
    if(pos >= 80)
    {
	pos = 0;
	off += 80;
    }
    if (off >= (80*25)){
	clear();
    }
    mem[off+pos] = (unsigned char) c | 0x0700;
    pos++;
}
