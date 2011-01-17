L  = ld
LF = -T linker.ld 

A  = nasm
AF = -f bin
AE = -f aout

C  = g++
CF = -c -nostdlib -fno-builtin -fno-rtti -fno-exceptions

ECHO = /bin/echo


image: clean bin bin/kernel.bin

bin/kernel.bin: bin/keyboard.o bin/video.o bin/interrupt.o bin/kernel.o bin/loader.o
	$(L) $(LF) -o bin/kernel.bin bin/loader.o bin/kernel.o bin/keyboard.o bin/video.o bin/interrupt.o
	$(ECHO) -ne \\x55\\xAA | dd conv=notrunc bs=1 seek=510 of=bin/kernel.bin

bin/kernel.o: kernel.cpp
	$(C) $(CF) -o bin/kernel.o kernel.cpp

bin/loader.o: loader.cpp
	$(C) $(CF) -Winline -o bin/loader.o loader.cpp

bin/keyboard.o: keyboard.cpp
	$(C) $(CF) -o bin/keyboard.o keyboard.cpp

bin/video.o: video.cpp
	$(C) $(CF) -o bin/video.o video.cpp

bin/interrupt.o: interrupt.cpp
	$(C) $(CF) -o bin/interrupt.o interrupt.cpp


bin:
	mkdir bin

clean:
	rm -rf ./bin
