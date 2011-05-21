#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <unistd.h>

#define POLL_TIMEOUT 500
#define BUFFER_SIZE 512


void quit(int exitCode, char * message){
	printf("%s", message);
	exit(exitCode);
}


void tryRead(int& fd){
	char buffer[BUFFER_SIZE + 1];
	struct pollfd fds;
	fds.fd = fd;
	fds.events = POLLIN | POLLNVAL | POLLERR | POLLHUP;
	
	if ((poll(&fds, 1,  POLL_TIMEOUT)) == -1) 
		quit(3, "ERROR poll");
		
	fprintf(stderr, "== %4d =================== try read =====================\n", fd);

	if (fds.revents & POLLIN) {
		size_t length = read(fd, buffer, BUFFER_SIZE);
		if (length == -1)
			quit(4, "ERROR read");
		if (length) {
			buffer[length] = '\0';
			fputs(buffer, stderr);
		}
		fprintf(stderr, "== %4d =================== readed %4d ==================\n", fd, length);
	}
	if (fds.revents & (POLLNVAL | POLLERR | POLLHUP)){
		fprintf(stderr, "== %4d =================== is closed ====================\n",fd, fds.revents);
		fd = -1;
	}

}

int main(int cdesc, char **argv) {
	cdesc--;
	int * desc = (int*)malloc(cdesc * sizeof(int));
	if (desc == NULL)
		quit(10, (char*)"ERROR malloc");

	for (int i = 1; i <= cdesc; ++i) {
		if (sscanf(argv[i], "%d", &desc[i-1]) != 1)
			quit(2, "ERROR parse");
	}

	while(true){
		for (int i = 0; i < cdesc; ++i) {
			if (desc[i] != -1)
				tryRead(desc[i]);
		}
		usleep(50000);
	}
	return 0;
}
