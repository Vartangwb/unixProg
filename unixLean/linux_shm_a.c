#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
int main()
{
	int id = shmget(0x8888, 4096, IPC_CREAT | IPC_EXCL | 0664);
	if(id < 0)
	{
		perror("shmget");
		return -1;
	}
	printf("id = %d\n", id);
	//将内核对象维护的内存挂接到指定线性地址
	char *buf = shmat(id, NULL, 0);
	if(buf == (char*)-1){
		perror("shmat");
		return -1;
	}
	strcpy(buf, "hellp, share memory~\n");
	if(shmdt(buf) < 0)
	{
		perror("shmdt");
		return -1;
	}
	return 0;
}
