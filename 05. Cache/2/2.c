#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define SIZE 100
//#define COUNT 6000000000LL
#define COUNT 100000000

void quit(int exitCode, char * message){
	printf("%s", message);
	exit(exitCode);
}

static void wait_thread(void)
{
	time_t start_time = time(NULL);
	while (time(NULL) == start_time);
}

volatile long long test_array[SIZE];

static void *thread_counter(void *args)
{
	int id;
	id = (int)args;
	
	for(test_array[id] = 0; test_array[id] < COUNT; test_array[id]++){
//		fprintf(stderr, "%d %lld              \r", id, test_array[id]);
	}
	pthread_exit(NULL);
}



int main(int argc, char *argv[])
{
	int secondThreadId = -1;
	if (argc != 2)
	    quit(1, "Usage: 2.img [f/s]\n");
	
	switch(argv[1][0]){
	    case 'f':
	    case 'F':
		secondThreadId = 10;
		break;
	    case 's':
	    case 'S':
		secondThreadId = 1;
		break;
	    default:		
		quit(2, "wrong arguments");		
	}

	cpu_set_t cpu1, cpu2;
	CPU_ZERO(&cpu1);
	CPU_SET(0, &cpu1);
	CPU_ZERO(&cpu2);
	CPU_SET(1, &cpu2);

	int i;
	pthread_t thread1;
	pthread_t thread2;

	if (pthread_create(&thread1, NULL, thread_counter, (void*)0) != 0)
		quit(11, "failed to create thread 1");
	if (pthread_create(&thread2, NULL, thread_counter, (void*)(secondThreadId)) != 0)
		quit(21, "failed to create thread 2");

	if (pthread_setaffinity_np(thread1, sizeof(cpu_set_t), &cpu1) != 0)
		quit(10, "failed to setaffinity thread 1");	
	if (pthread_setaffinity_np(thread1, sizeof(cpu_set_t), &cpu2) != 0)
		quit(20, "failed to setaffinity thread 2");	
		
	if (pthread_join(thread1, NULL) != 0)
		quit(12, "failed join thread 1");
	if (pthread_join(thread2, NULL) != 0)
		quit(22, "failed join thread 2");
	return 0;
}
