int main()
{
    unsigned short *video = (unsigned short *)0xB8000;
    video[0] = 0xE020;
}
