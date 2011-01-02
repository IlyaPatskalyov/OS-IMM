#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#define KEYBOARD_BUFFER_SIZE 0x20
class Keyboard
{
public:
	void init();
	void interrupt();
	bool isEmpty();
	char get();
private:
	int special(unsigned char code);
	
	unsigned short buffer_head, buffer_tail;
	char buffer[KEYBOARD_BUFFER_SIZE];
	bool shift, ctrl, alt, caps, spec;
	static char mapNormal[], mapShifted[], capsNormal[], capsShifted[];
};

#endif