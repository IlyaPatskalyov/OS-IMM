#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <unistd.h>

#define POLL_TIMEOUT 5000
#define BUFFER_SIZE 512

int count, countAlive;
bool *isAlive;
struct pollfd *fds;

void quit(int exitCode, char * message){
	if (isAlive != NULL)
		free(isAlive);
	if (fds != NULL)
		free(fds);
	fprintf(stderr, "%s", message);
	exit(exitCode);
}


void tryRead(pollfd & fd, bool &isAlive) {
	char buffer[BUFFER_SIZE + 1];
//	fprintf(stderr, "== %4d =================== try read =====================\n", fd.fd);
	if (fd.revents & POLLIN) {
		size_t length = read(fd.fd, buffer, BUFFER_SIZE);
		switch(length){
			case 0:
			case -1:
				fprintf(stderr, "== %4d ================== can't read ====================\n", fd.fd);
				isAlive = false;
				countAlive--;
				break;
			default:
				fprintf(stderr, "== %4d =================== readed %4d ==================\n", fd.fd, length);
				write(1, buffer, length);
		}
	}
	if (fd.revents & (POLLNVAL | POLLERR | POLLHUP)) {
		fprintf(stderr, "== %4d ==================== is dead =====================\n",fd);
		isAlive = false;
		countAlive--;
	}
}

int main(int argc, char **argv) {
	count = argc - 1;
	isAlive = (bool*)malloc(count * sizeof(bool));
	fds = (struct pollfd *)malloc(count * sizeof(struct pollfd*));

	if (isAlive == NULL || fds == NULL)
		quit(10, (char*)"ERROR malloc");

	for (int i = 0; i < count; ++i) {
		int id;
		if (sscanf(argv[i+1], "%d", &id) != 1)
			quit(2, (char*)"ERROR parse");
		fds[i].fd = id;
		fds[i].events = POLLIN | POLLNVAL | POLLERR | POLLHUP;
		isAlive[i] = true;
	}

	countAlive = count;
	while(countAlive){
		if (poll(fds, count,  POLL_TIMEOUT) == -1) 
			quit(3, (char*)"ERROR poll");
		
		for (int i = 0; i < count; i++)
			if (isAlive[i])
				tryRead(fds[i], isAlive[i]);
	}
	
	quit(0, (char*)"Ok");
	return 0;
}