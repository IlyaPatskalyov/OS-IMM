#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

void quit(int exitCode, char * message){
	printf("%s", message);
	exit(exitCode);
}

static void wait_thread(void)
{
	time_t start_time = time(NULL);
	while (time(NULL) == start_time);
}

static void *thread_counter(void *args)
{
	int id;
	long long counter;
	id = (int)args;
	
	for(counter = 0; counter < 6000000000LL; counter++){
		fprintf(stderr, "%d %lld\r", id, counter);
	}
	pthread_exit(NULL);
}


static void *thread_test(void *args)
{
	int i, id;
	id = (int)args;
	for (i = 0; i < 20; i++)
	{
		fprintf(stderr, "%d", id);
		wait_thread();
	}
	pthread_exit(NULL);
}


int main(void)
{
	int i;
	pthread_t thread1;
	pthread_t thread2;

	if (pthread_create(&thread1, NULL, thread_counter, (void*)1) != 0)
		quit(11, "failed to create thread 1");
	if (pthread_create(&thread2, NULL, thread_counter, (void*)2) != 0)
		quit(21, "failed to create thread 2");
	if (pthread_join(thread1, NULL) != 0)
		quit(12, "failed join thread 1");
	if (pthread_join(thread2, NULL) != 0)
		quit(22, "failed join thread 2");
	return 0;
}
