L  = ld
LF = -T linker.ld 

A  = nasm
AF = -f bin
AE = -f aout

C  = g++
CF = -c -nostdlib -fno-builtin -fno-rtti -fno-exceptions


image: clean bin bin/kernel.bin

bin/kernel.bin: bin/boot.o bin/video.o bin/kernel.o
	$(L) $(LF) -o bin/kernel.bin bin/boot.o bin/kernel.o bin/video.o

bin/kernel.o: kernel.cpp bin/video.o
	$(C) $(CF) -o bin/kernel.o kernel.cpp

bin/video.o: video.cpp
	$(C) $(CF) -o bin/video.o video.cpp

bin/boot.o: boot.asm
	$(A) $(AE) -o bin/boot.o boot.asm

bin:
	mkdir bin

clean:
	rm -rf ./bin
