L  = ld
LF = -T linker.ld 

A  = nasm
AF = -f bin
AE = -f aout

C    = g++
CF   = -lpthread

image: clean life.out

life.out:
	$(C) $(CF) -o life.out lifecalc.cpp life.cpp

clean:
	rm -f life.out
