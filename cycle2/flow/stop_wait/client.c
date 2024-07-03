#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void main()
{
	char buffer[1024];
	struct sockaddr_in s_a;
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

	int packetcount=1;
	while(packetcount<=6)
	{
		// int packet=1;
		// char buffer[50];
		printf("Client : Sending packet %d\n",packetcount);
		sprintf(buffer,"%d",packetcount);
		sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&s_a,sizeof(s_a));
		bzero(buffer,1024);
		size_ad=sizeof(s_a);
		recvfrom(sockfd,buffer,1024,0,(struct sockaddr *)&s_a,&size_ad);
		printf("Client : Received acknowledgement for packet %s\n",buffer);
		packetcount++;
	}
	
	



}

