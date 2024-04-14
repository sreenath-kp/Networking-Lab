#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void main()
{
	char buffer[1024];
	struct sockaddr_in s_a,c_a;
	int sockfd;
	socklen_t size_ad;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0)
	{	
		printf("error");
		exit(1);
	}
	memset(&s_a,'\0',sizeof(s_a));
	s_a.sin_family=AF_INET;
	s_a.sin_port=htons(8609);
	s_a.sin_addr.s_addr=inet_addr("127.0.0.1");

	int n=bind(sockfd,(struct sockaddr *)&s_a,sizeof(s_a));
	if(n<0)
	{
		printf("error\n");
		exit(1);
	}
	while(1)
	{

		bzero(buffer,1024);
		size_ad=sizeof(s_a);
		recvfrom(sockfd,buffer,1024,0,(struct sockaddr *)&s_a,&size_ad);
		printf("Server : Received packet : %s\n",buffer);
		sleep(1);
		printf("Server : Sending acknowledgement for packet : %s\n",buffer);

		sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&s_a,sizeof(s_a));

		// if(strcmp(buffer,"10")=)
	}
	

}
