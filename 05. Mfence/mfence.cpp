#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define SIZE 100
#define COUNT 10000000

volatile bool flags[] ={ false, false};
volatile bool turn = 0;
volatile long long counter = 0;

void quit(int exitCode, char * message) {
	printf("%s", message);
	exit(exitCode);
}

inline static __attribute__ ((always_inline))
void mfence(){
	asm volatile ("mfence" : : :"memory");
}

void lock(char id) {
	flags[id] = true;
	mfence();
	while (flags[id^1]){
		if (turn != id) {
			flags[id] = false;
			while (turn!=id) ;
			flags[id] = true;
			mfence();
		}
	}
}

void unlock(char id) {
	*(flags+id) = false;
	turn = id ^ 1;

}

static void *thread_counter(void *args)
{
	int id = (int)args;
	for(int i = 0; i < COUNT; i++){
		lock(id);
		++counter;
		unlock(id);
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

	if (pthread_create(&thread1, NULL, thread_counter, (void*)0) != 0)
		quit(11, (char*)"failed to create thread 1");
	if (pthread_create(&thread2, NULL, thread_counter, (void*)1) != 0)
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
