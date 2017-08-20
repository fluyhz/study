#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXLINE 4096

int main(int argc, char** argv)
{
	int sockfd, n, rec_len;
	char recvline[MAXLINE], sendline[MAXLINE];
	char buf[MAXLINE];
	struct sockaddr_in servaddr;
	
	if(argc !=2 )
	{
		std::cout<<"usage: ./client <ipaddress>"<<std::endl;
		exit(0);
	}

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout<<"create socket error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<std::endl;
		exit(0);
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8000);
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
	{
		std::cout<<"inet_pton error for "<<argv[1]<<std::endl;
		exit(0);
	}

	if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	{
		std::cout<<"connect socket error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<std::endl;
		exit(0);
	}
	std::cout<<"send msg to server:"<<std::endl;
	fgets(sendline, MAXLINE, stdin);
	if( send(sockfd, sendline, strlen(sendline),0) < 0)
	{
		std::cout<<"send msg error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<std::endl;
		exit(0);
	}
	if((rec_len = recv(sockfd, buf, MAXLINE, 0)) == -1)
	{
		perror("recv error");
		exit(1);
	}
	buf[rec_len] = '\n';
	std::cout<<"Received : "<<buf<<std::endl;
	close(sockfd);
	exit(0);
}
