#include <stdio.h>  
#include <unistd.h>  
#include <sys/time.h>  
  
int selectdemo()  
{  
    fd_set rfds;  
    FD_ZERO(&rfds);  
    FD_SET(STDIN_FILENO, &rfds);  
  
    fd_set wfds;  
    FD_ZERO(&wfds);  
    FD_SET(STDOUT_FILENO, &wfds);  
      
    struct timeval tv;  
    tv.tv_sec = 5;  
    tv.tv_usec = 0;  
    int retval = select(STDOUT_FILENO + 1, &rfds, &wfds, NULL, &tv);  
    if (retval < 0)  
    {  
        printf("select error\n");  
        return -1;  
    }  
  
    if (retval == 0)  
    {  
        printf("time out\n");  
        return -1;  
    }  
  
  
    // 需要对所有句柄进行轮询遍历  
    if(FD_ISSET(STDIN_FILENO, &rfds))  
    {  
        printf("can read\n");  
    }  
  
    if(FD_ISSET(STDOUT_FILENO, &wfds))  
    {  
        printf("can write\n");  
    }  
  
    return 0;        
}  
int main()  
{  
    selectdemo();  
   // play_poll();  
   // play_epoll();  
  
    return 0;  
}  
