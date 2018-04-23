#include<stdio.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<pthread.h>
#include<strings.h>

int main()
{
	int socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(socketfd, (struct sockaddr*)&saddr, sizeof(struct sockaddr_in))<0)
		perror("bind error");
	struct sockaddr_in cliaddr;
	int s = sizeof(struct sockaddr);
	char buf[20];
	char buf1[20];
	int n;
	while(1){
		bzero(buf, 20);
		if(n = recvfrom(socketfd, buf, 20, 0, (struct sockaddr *)&cliaddr,&s)<0)
			perror("send error");
		printf("%s", buf);
		fgets(buf1, 20, stdin);
		sendto(socketfd, buf1, strlen(buf),0,(struct sockaddr * )&cliaddr,s);
	}
	close(socketfd);
}
