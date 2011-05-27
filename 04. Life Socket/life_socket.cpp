#include <signal.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <aio.h>
#include "utils.h"
#include "buffer.h"
#include "pool.h" 
#include "aiob.h"
#include "../03. Life Console/lifecalc.h"

const int TCP_PORT = 5002;
const int MAX_X = 40;
const int MAX_Y = 40;
char BUFFER_NOT_FOUND_MESSAGE[] = "HTTP/1.0 503 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nCouldn't process your request\n";

Pool pool;
pthread_mutex_t Pool::poolLock = PTHREAD_MUTEX_INITIALIZER; 
unsigned int Pool::countFreeBuffers = POOL_SIZE;

static void *life_thread(void *args){
	srand(time(NULL));
	while(true){
		Buffer * newBuffer = pool.initBuffer();
		iterateLife(MAX_X, MAX_Y, pool.getThisBuffer()->buffer, newBuffer->buffer, false);
		pool.setThisBuffer(newBuffer);
		sleep(1);
	}
}

static void *accept_thread(void *args){
	int sockfd = (int)args, newsockfd;
	sockaddr_in cli_addr;
	socklen_t clilen = sizeof(cli_addr);
	while (newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen)){
		if (newsockfd < 0)
			quit(3, (char*)"ERROR accept");
		Buffer *buffer = pool.attachClient();
		Aio * item;
		if (buffer != NULL)
			item = new Aio(newsockfd, &pool, buffer);
		else
			item = new Aio(newsockfd, BUFFER_NOT_FOUND_MESSAGE);
	}
}

int sockfd;
void close_socket_signal(int x){
	if (close(sockfd));
		quit(1, (char*)"ERROR close main socket");
	quit(0, (char*)"Exit");
}

int main() {
	generateCells(MAX_X, MAX_Y, pool.getThisBuffer()->buffer);
	
	pthread_t life_pthread, accept_pthread;
	if (pthread_create(&life_pthread, NULL, life_thread, NULL) != 0)
		quit(11, (char*)"ERROR failed to create life thread");
	
	sockfd = bind_server(TCP_PORT);
	signal(SIGINT, close_socket_signal);
	if (pthread_create(&accept_pthread, NULL, accept_thread, (void*)sockfd) != 0)
		quit(12, (char*)"ERROR failed to create accept thread");
	
	if (pthread_join(accept_pthread, NULL) != 0)
		quit(21, (char*)"ERROR failed join life thread");
	if (pthread_join(life_pthread, NULL) != 0)
		quit(22, (char*)"ERROR failed join accpet thread");
	return 0;
}
