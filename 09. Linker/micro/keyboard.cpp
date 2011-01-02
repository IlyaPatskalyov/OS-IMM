#include "base.h"
#include "keyboard.h"

char Keyboard::mapNormal[] = { 0x00,0x1B,'1','2','3','4','5','6','7','8','9','0','-','=','\r','\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0x80,'a','s','d','f','g','h','j','k','l',';',0x2F,0x8C,0x80,0x86,'z','x','c','v','b','n','m',',','.','/',0x80,'*',0x80,' ',0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,'0',0xB1 };
char Keyboard::mapShifted[] = { 0x00,0x21,'!','@','#','$','%','^','&','*','(',')','_','+','\r','\t','Q','W','E','R','T','Y','U','I','O','P','{','}',0x0F,0x80,'A','S','D','F','G','H','J','K','L',':',0x2A,'~',0x80,'|','Z','X','C','V','B','N','M','<','>','?',0x80,'*',0x80,' ',0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,'7','8','9',0x80,'4','5','6',0x80,'1','2','3','0',0xB1};
char Keyboard::capsNormal[] = { 0x00,0x1B,'1','2','3','4','5','6','7','8','9','0','-','=','\r','\t','Q','W','E','R','T','Y','U','I','O','P','[',']','\n',0x80,'A','S','D','F','G','H','J','K','L',';',0x2F,0x8C,0x80,'|','Z','X','C','V','B','N','M',',','.','/',0x80,'*',0x80,' ',0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,'0',0xB1};
char Keyboard::capsShifted[] = {0,0x1B,'!','@','#','$','%','^','&','*','(',')','_','+','\r','\t','q','w','e','r','t','y','u','i','o','p','{','}',015,0x80,'a','s','d','f','g','h','j','k','l',':',0x2A,'~',0x80,0x86,'z','x','c','v','b','n','m','<','>','?',0x80,'*',0x80,' ',0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,'7','8','9',0x80,'4','5','6',0x80,'1','2','3','0',0xB1};


void Keyboard::init(){
	buffer_head = 0;
	buffer_tail = 0;
}

char Keyboard::get(){
	char c = buffer[buffer_tail];
	buffer_tail = (buffer_tail+1) % KEYBOARD_BUFFER_SIZE;
	return c;
}

bool Keyboard::isEmpty(){
	return buffer_head == buffer_tail;
}

int Keyboard::special(unsigned char code){
	switch(code)	{
		case 0x36: //R-Shift down
		case 0x2A: //L-Shift down
			shift = true;
			break;
		case 0xB6: //R-Shift up
		case 0xAA: //L-Shift up
			shift = false;
			break;
		case 0x1D: //Control down
			ctrl = true;
			break;
		case 0x9D: //Control up
			ctrl = false;
			break;
		case 0x38: //Alt down
			alt = true;
			break;
		case 0xB8: //Alt up
			alt = false;
			break;
		case 0x3A: //Caps down
			if(spec == true){
				caps = !caps;
				spec = false;
			}
			break;
		case 0xBA: //Caps Up
			spec = true;
			break;
		case 0xE0:
			break;
		default:
			return 0;
		}
	return 1;
}

void Keyboard::interrupt(){
	unsigned char scanCode = inb(0x60), asciiCode;
	outb(0x20, 0x20);

	if(!(Keyboard::special(scanCode) | (scanCode >= 0x80))){
		if(shift)
			if(!caps)
				asciiCode = Keyboard::mapShifted[scanCode];
			else
				asciiCode = Keyboard::capsShifted[scanCode];
		else
			if(!caps)
				asciiCode = Keyboard::mapNormal[scanCode];
			else
				asciiCode = Keyboard::capsNormal[scanCode];
		buffer[buffer_head] = asciiCode;
		buffer_head = (buffer_head+1) % KEYBOARD_BUFFER_SIZE;
	}
}
