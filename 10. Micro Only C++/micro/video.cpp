#include "video.h"
#include "base.h"

Video::Video()
{
	init();
}


void Video::init()
{
	pos = 0;
	off = 0;
	mem = (unsigned short*)0xB8000;
	crtc = 0x3D4;
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
	if(c == '\r' && !(off == 0 && pos == 0)){
		if (pos > 0)
			pos--;
		mem[off+pos] = 0x0700;
		setcursor();
		return;
	}
	if(pos >= 80 || c == '\n')
	{
		pos = 0;
		off += 80;
		setcursor();
	}
	if (off >= (80*25)){
		newline();
	}
	if (c >= ' '){
		mem[off+pos] = (unsigned char) c | 0x0700;
		pos++;
		setcursor();
	}
}

void Video::newline(){
	for(int i = 0; i < (80*24); i++) 
		mem[i] = mem[i+80];
	for(int i = 0; i < 80; i++)
		mem[80*24+i] = 0x0700;
	pos = 0;
	off -= 80;
}

void Video::setcursor()
{
	outb(crtc, 14); 
	outb(crtc+1, (off+pos)>> 8);
	outb(crtc, 15);
	outb(crtc+1, (off+pos));
}
