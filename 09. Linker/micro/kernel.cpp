#include "video.h"

extern "C" void timer(){
    Video v;
    v.write("Hello, world!");
}

int main(void)
{
    Video v;
    v.clear();
//    v.write("Hello, world!");
}
