#include<unistd.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdio.h>
#include<stdlib.h>

#define R0 0
#define R1 1
#define R2 2

void printSem(int id)
{
	unsigned short vals[3] = {0};
	semctl(id, 3, GETALL, vals);
	printf("R0 = %d, R1 = %d, R2 = %d\n\n", vals[0], vals[1], vals[2]);
}

int main()
{
	int id = semget(0x8888, 3, IPC_CREAT | IPC_EXCL | 0664 );
	puts("信号量初始值:");
	printSem(id);
	
	puts("设置第二个信号量的值:");
	semctl(id, 2, SETVAL, 20);
	printSem(id);

	puts("同时设置3个信号量的值");
	unsigned short vals[3] = {12, 5, 9};
	semctl(id, 0, SETALL, vals);
	printSem(id);

	puts("请求2个R0资源");
	struct sembuf op1 = {0, -2, 0};
	semop(id, &op1, 1);
	printSem(id);

	puts("请求3个R1和5个R2");
	struct sembuf ops1[2] = {
		{1, -3, 0}, {2, -5, 0}
	};	
	semop(id, ops1, 2);
	printSem(id);

	puts("删除");
	semctl(id, 0, IPC_RMID);
	return 0;	



	


}
