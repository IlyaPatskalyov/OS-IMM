#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void quit(int exitCode, char * message){
	printf("%s", message);
	exit(exitCode);
}



int bind_server(int portno){
	int sockfd;
	sockaddr_in serv_addr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		quit(1, (char*)"ERROR opening socket");
	memset(&(serv_addr), '\0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		quit(2, (char*)"ERROR bind");
	listen(sockfd,5);
	return sockfd;
}
