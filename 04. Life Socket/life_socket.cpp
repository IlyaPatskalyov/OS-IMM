#include <signal.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <aio.h>
#include <queue>
#include "utils.h"
#include "buffer.h"
#include "aiob.h"
#include "../03. Life Console/lifecalc.h"

const int TCP_PORT = 5001;
const int COUNT_BUFFERS = 1000;
const int MAX_X = 40;
const int MAX_Y = 40;
char BUFFER_NOT_FOUND_MESSAGE[] = "HTTP/1.0 503 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nCouldn't process your request\n";

pthread_mutex_t buffers_lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER; 
unsigned int lastCalcBuffer = 0, Buffer::countFreeBuffers = COUNT_BUFFERS;
std::queue<int> queuec;
Buffer cb[COUNT_BUFFERS];

static void *life_thread(void *args){
	srand(time(NULL));
	for(;;){
		int newBuffer;
		if (pthread_mutex_lock(&buffers_lock))
			quit(31, (char*)"ERROR lock buffers");

		for(int i = 0; i < COUNT_BUFFERS; i++){
			if (i != lastCalcBuffer && cb[i].countClients == 0){
				newBuffer = i;
				break;
			}
		}
		if (pthread_mutex_unlock(&buffers_lock))
			quit(32, (char*)"ERROR unlock buffers");


		iterateLife(MAX_X, MAX_Y, cb[lastCalcBuffer].buffer, cb[newBuffer].buffer, false);

		if (pthread_mutex_lock(&buffers_lock))
			quit(31, (char*)"ERROR lock buffers");
		lastCalcBuffer = newBuffer;
		if (pthread_mutex_unlock(&buffers_lock))
			quit(32, (char*)"ERROR unlock buffers");


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
		if (pthread_mutex_lock(&queue_lock))
			quit(33, (char*)"ERROR lock queue");

		queuec.push(newsockfd);

		if (pthread_mutex_unlock(&queue_lock))
			quit(34, (char*)"ERROR unlock queue");
	}
}

void process_client(int sock){
	Aio * item;

	if (pthread_mutex_lock(&buffers_lock))
		quit(31, (char*)"ERROR lock buffers");

	Buffer *currentBuffer = &cb[lastCalcBuffer];
	if (currentBuffer->canGet()){
		currentBuffer->get(sock);
		item = new Aio(sock, currentBuffer, &buffers_lock);
	}
	else
		item = new Aio(sock, BUFFER_NOT_FOUND_MESSAGE);


	if (pthread_mutex_unlock(&buffers_lock))
		quit(32, (char*)"ERROR unlock buffers");

	item->write();
}

int sockfd;

void close_socket_signal(int x){
	if (close(sockfd));
		quit(1, (char*)"ERROR close main socket");
	quit(0, (char*)"Exit");
}

int main() {
	generateCells(MAX_X, MAX_Y, cb[0].buffer);
	pthread_t life_pthread, accept_pthread;
	if (pthread_create(&life_pthread, NULL, life_thread, NULL) != 0)
		quit(11, (char*)"ERROR failed to create life thread");
	
	sockfd = bind_server(TCP_PORT);
	signal(SIGINT, close_socket_signal);
	if (pthread_create(&accept_pthread, NULL, accept_thread, (void*)sockfd) != 0)
		quit(12, (char*)"ERROR failed to create accept thread");
	
	while(true){
		while(true){
			if (pthread_mutex_lock(&queue_lock))
			    quit(33, (char*)"ERROR lock queue");
			if (queuec.empty()){
				if (pthread_mutex_unlock(&queue_lock))
					quit(32, (char*)"ERROR unlock queue");
				break;
			}
			int clientsockfd = queuec.front();
			queuec.pop();
			if (pthread_mutex_unlock(&queue_lock))
				quit(32, (char*)"ERROR unlock queue");
			process_client(clientsockfd);
		}
		usleep(1000);
	}
	return 0;
}


