class Video
{
public:
    void init();
    void clear();
    void write(char *cp);
    void put(char c);
private:
    void nextline();
    unsigned short *mem;
    unsigned int off;
    unsigned int pos;
};
