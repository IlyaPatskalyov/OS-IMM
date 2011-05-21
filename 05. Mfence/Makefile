C    = g++
CF   = -lpthread  -O3
#-S -g 
D    = objdump -d -Mintel-mnemonics 

image: clean mfence.out

mfence.out:
	$(C) $(CF) -o mfence.out mfence.cpp
	$(C) $(CF) -o mfence.out.stupid mfence.stupid.cpp
	$(D) mfence.out > mfence.out.dump
	$(D) mfence.out.stupid > mfence.out.stupid.dump
	

clean:
	rm -f mfence.out*
