#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define SIZE 100
#define COUNT 10000000

volatile bool flags1 =false, flags0 = false;
volatile bool turn = 0;
volatile long long counter;

void quit(int exitCode, char * message) {
	printf("%s", message);
	exit(exitCode);
}

inline static __attribute__ ((always_inline))
void mfence(){
	asm volatile ("mfence" : : :"memory");
}

void lock1() {
	flags1 = true;
	mfence();
	while (flags0){
		mfence();
		if (!turn) {
			flags1 = false;
			mfence();
			while (!turn) ;
			flags1 = true;
			mfence();
		}
	}
}

void unlock1() {
	flags1 = false;
	turn = 0;
}

void lock0() {
	flags0 = true;
	mfence();
	while (flags1){
		mfence();
		if (turn) {
			flags0 = false;
			mfence();
			while (turn);
			flags0 = true;
			mfence();
		}
	}
}

void unlock0() {
	flags0 = false;
	turn = 1;
}

static void *thread_counter0(void *args)
{
	for(int i = 0; i < COUNT; i++){
		lock0();
		++counter;
		unlock0();
	}
	pthread_exit(NULL);
}

static void *thread_counter1(void *args)
{
	for(int i = 0; i < COUNT; i++){
		lock1();
		++counter;
		unlock1();
	}
	pthread_exit(NULL);
}


int main(){
	cpu_set_t cpu1, cpu2;
	CPU_ZERO(&cpu1);
	CPU_SET(0, &cpu1);
	CPU_ZERO(&cpu2);
	CPU_SET(1, &cpu2);

	pthread_t thread1;
	pthread_t thread2;

	if (pthread_create(&thread1, NULL, thread_counter0, (void*)0) != 0)
		quit(11, (char*)"failed to create thread 1");
	if (pthread_create(&thread2, NULL, thread_counter1, (void*)1) != 0)
		quit(21, (char*)"failed to create thread 2");

	if (pthread_setaffinity_np(thread1, sizeof(cpu_set_t), &cpu1) != 0)
		quit(10, (char*)"failed to setaffinity thread 1");
	if (pthread_setaffinity_np(thread2, sizeof(cpu_set_t), &cpu2) != 0)
		quit(20, (char*)"failed to setaffinity thread 2");
		
	if (pthread_join(thread1, NULL) != 0)
		quit(12, (char*)"failed join thread 1");
	if (pthread_join(thread2, NULL) != 0)
		quit(22, (char*)"failed join thread 2");
		
	printf("%lld\n", counter);
	return 0;
}
