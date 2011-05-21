L  = ld
LF = -T linker.ld 

A  = nasm
AF = -f bin
AE = -f aout

C    = g++
CF   = -lpthread -lrt

image: clean life.out

life.out:
	$(C) $(CF) -o life.out utils.cpp "../03. Life Console/lifecalc.cpp" life_socket.cpp

clean:
	rm -f life.out
