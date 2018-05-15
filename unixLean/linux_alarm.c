#include<unistd.h>
#include<signal.h>
#include<stdio.h>
void handler(int sig)
{
	if(sig == SIGALRM)
		printf("Bomb!!!!\n");
}

int main()
{
	if(SIG_ERR == signal(SIGALRM, handler)){
		perror("signal SIGALRM");
	}
	unsigned int remain = 0;
	remain = alarm(5);
	printf("the previous alarm remain %d secs\n", remain);
	sleep(3);
	remain = alarm(3);
	printf("the previous alarm remain %d\n", remain);
	while(1)
	{
		write(STDOUT_FILENO, ".", 1);
		pause();
	}
}
