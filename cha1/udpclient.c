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
int socketfd = socket(AF_INET,SOCK_DGRAM,0);//、、、、、、、1.创建udp套接字得到socketfd文件描述符
    struct sockaddr_in saddr;
    memset(&saddr,0,sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(6000);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");//、、、2.初始化结构体sockaddr_in 目标主机的ip,sendto的倒数第二个参数

    
    struct sockaddr_in caddr;
    int s = sizeof(struct sockaddr);    
    char buf[20],buf1[20];
    int n;
    while(1)//、、、、3.发送接收数据.
    {    
        //bzero(buf,20);    
        fgets(buf,20,stdin);
        if(n = sendto(socketfd,buf,strlen(buf),0,(struct sockaddr *)&saddr,s)<0)
            perror("recv() error!\n");
        //    printf("%d\n",n);
        bzero(buf1,20);
        recvfrom(socketfd,buf1,20,0,(struct sockaddr *)&caddr,&s);
        printf("%s",buf1);
    }    
    close(socketfd);//、、、4.关闭socketfd

}
