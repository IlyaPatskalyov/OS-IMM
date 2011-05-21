#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <stdlib.h>
#include "lifecalc.h"

void quit(int exitCode, char * message){
	printf("%s", message);
	exit(exitCode);
}

pthread_mutex_t print_lock = PTHREAD_MUTEX_INITIALIZER; 
const bool bIsTor = false;
const int COUNT_BUFFERS = 3;
volatile int nCol = 40, nRow = 40, lastCalcBuffer = 0, printBuffer = -1;
char buffer[COUNT_BUFFERS][15000];

static void *life_thread(void *args){
	srand(time(NULL));
	for(;;){
		int newBuffer = -1;
		pthread_mutex_lock(&print_lock);
		for(int i = 0; i < COUNT_BUFFERS; i++){
			if (i != lastCalcBuffer && i != printBuffer){
				newBuffer = i;
				break;
			}
		}
		pthread_mutex_unlock(&print_lock);

		iterateLife(nCol, nRow, buffer[lastCalcBuffer], buffer[newBuffer], bIsTor);
		
		pthread_mutex_lock(&print_lock);
		lastCalcBuffer = newBuffer;
		pthread_mutex_unlock(&print_lock);
		sleep(1);
	}
}

static void *print_thread(void *args){
	char c;
	for(;;){
		if (scanf("%c", &c)){
			pthread_mutex_lock(&print_lock);
			printBuffer = lastCalcBuffer;
			pthread_mutex_unlock(&print_lock);
			
			puts(buffer[printBuffer]);

			pthread_mutex_lock(&print_lock);
			printBuffer = -1;
			pthread_mutex_unlock(&print_lock);
		}

	}
}

int main() {
	generateCells(nCol, nRow, buffer[0]);
	
	pthread_t thread1, thread2;

	if (pthread_create(&thread1, NULL, life_thread, NULL) != 0)
		quit(11, (char*)"failed to create thread 1");
	if (pthread_create(&thread2, NULL, print_thread, NULL) != 0)
		quit(21, (char*)"failed to create thread 2");

	if (pthread_join(thread1, NULL) != 0)
		quit(12, (char*)"failed join thread 1");
	if (pthread_join(thread2, NULL) != 0)
		quit(22, (char*)"failed join thread 2");
		
	return 0;
}

