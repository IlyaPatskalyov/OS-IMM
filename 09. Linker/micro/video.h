#ifndef __VIDEO_H__
#define __VIDEO_H__

class Video
{
public:
	Video();
	void init();
	void clear();
	void write(char *cp);
	void put(char c);
private:
	void newline();
	void setcursor();
	unsigned short *mem, crtc;
	unsigned int off;
	unsigned int pos;
};

#endif