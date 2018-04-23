#include<sys/types.h>
#include<sys/socket.h>
#include <strings.h>                                                                                
#include <ctype.h>                                                                                  
#include <stdio.h>                                                                                  
#include <stdlib.h>                                                                                 
#include <unistd.h>                                                                                 
#include <arpa/inet.h>                                                                              
#define SERV_PORT 8001
void perr_exit(const char * str)
{
	perror(str);
	exit(1);
} 
int main()
{
	int sfd = socket(AF_INET,SOCK_STREAM,0),cfd;
	struct sockaddr_in servaddr;
	struct sockaddr_in client_addr;
	int i, len;
	socklen_t addr_len;
	bzero(&servaddr, sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	
	//htons htonl 属于网络字节序转换
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sfd, (struct sockaddr*)&servaddr, sizeof(servaddr) ) < 0)
	perr_exit("bind error");
	listen(sfd, 128);
	
	printf("wait\n");
	addr_len = sizeof(client_addr);
	cfd = accept(sfd, (struct sockaddr *)&client_addr, &addr_len);
	if(cfd == -1)
		perr_exit("accept error");
	char buf[256];
	printf("client IP :%s %d\n",                                                                    
            inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,buf,sizeof(buf)),                        
          ntohs(client_addr.sin_port));       
while(1)                                                                                        
    {                                                                                               
        len = read(cfd,buf,sizeof(buf)); //读取客户端的数据                                         
        printf("%d", len);
	if(len == -1)                                                                               
            perr_exit("read error");
        /*
          if(len == 0)                                                                                
        {                                                                                           
            printf("the other size closed\n");                                                             
            close(cfd);                                                                             
            close(sfd);                                                                             
            exit(1);                                                                                
        }           
        */                                                                    
        if(write(STDOUT_FILENO,buf,len) < 0) //输出到屏幕                                           
            perr_exit("write error");                                                               
        for(i = 0 ;i < len ; i++)   //进行大写转换                                                  
            buf[i] = toupper(buf[i]);                                                               
        if(write(cfd,buf,len) < 0) //写数据到客户端                                                 
            perr_exit("write error");                                                               
    }                                                                                               
    //关闭打开的文件描述符，虽然不会执行到这里往下的部分，但要养成良好习惯，打开文件描述符，用完    
    //就要关闭                                                                                      
    close(sfd);                                                                                     
    close(cfd);                                                                                     
    return 0;         

	
}
