//服务端程序代码
//客户端向服务器监听端口发送请求，服务器将系统的当前时间发送给客户端
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXFD 64
#define MAXLINE 255
#define PORT 1234
#define BACKLOG 5
#define TIMESIZE 64

void daemon_init(const char *pname, int facility){
	int i;
	pit_t pid;
	if((pid = fork()) != 0){
		exit(0);
	}
	setsid();
	signal(SIGHUP, SIG_IGN);//signal表示信号函数，第一个参数表示需要处理的信号值，第二个表示一个信号处理函数或者信号表示
	if((pid = fork())!=0){
		exit(0);
	}
	chdir("/");
	umask(0);
	for(int i = 0; i<MAXFD;i++){
		close(i);
	}
	openlog(pname, LOG_PID, facility);
	
}

void getcurtime(char *curtime){
	time_t tm;
	time(&tm);
	snprintf(curtime, TIMESIZE, "%s", ctime(&tm));
}


