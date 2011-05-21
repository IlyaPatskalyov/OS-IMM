#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

char buff[100];

void sigint(int x)
{
	fputs(buff, stderr);
	exit(0);
}

void sigtstp(int x)
{
	signal(SIGTSTP,sigtstp); /* reset signal */
	fputs(buff, stderr);
}


int main()
{
	sprintf(buff, "PID: %d; PGID: %d\n", getpid(), getpgid(getpid()));
	signal(SIGTSTP,sigtstp);
	signal(SIGINT,sigint);
	for(;;){
		sleep(5);
	}
}


