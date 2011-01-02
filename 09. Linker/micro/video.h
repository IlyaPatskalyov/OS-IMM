#ifndef __VIDEO_H__
#define __VIDEO_H__

class Video
{
public:
	void init();
	void clear();
	void write(char *cp);
	void put(char c);
private:
	void newline();
	unsigned short *mem;
	unsigned int off;
	unsigned int pos;
};

#endif