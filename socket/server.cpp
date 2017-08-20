#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#define DEFAULT_PORT 8000
#define MAXLINE 4096
int main(int argc, char** argv)
{
	int socket_fd, connect_fd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	int n;
	// initial socket
	if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		std::cout<<"create socket error:"<<strerror(errno)<<"(errno:"<<errno<<")"<<std::endl;
		exit(0);
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(DEFAULT_PORT);
	if( bind(socket_fd,(struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
	{
		std::cout<<"bind socket error:"<<strerror(errno)<<"(errno:"<<errno<<")"<<std::endl;
		exit(0);
	}
	if( listen(socket_fd, 10) == -1)
	{
		std::cout<<"listen socket error:"<<strerror(errno)<<"(errno:"<<errno<<")"<<std::endl;
		exit(0);
	}
	std::cout<<"=======waiting for client's request======"<<std::endl;
	while(1)
	{
		if( (connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1)
		{
			std::cout<<"accept socket error:"<<strerror(errno)<<"(errno:"<<errno<<")"<<std::endl;
			continue;
		}
		n = recv(connect_fd, buff, MAXLINE, 0);
		if(!fork())
		{
			if(send(connect_fd, "Hello, you are connected!\n", 26,0) == -1)
				perror("send error");
			close(connect_fd);
			exit(0);
		}
		buff[n] = '\0';
		std::cout<<"recv msg from client: "<<buff<<std::endl;
		close(connect_fd);
	}
	close(socket_fd);
}
