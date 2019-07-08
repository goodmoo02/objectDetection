#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//For IPC 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#define SHMSIZE	100 //int * 100

int main(void)
{
	void *shared_Mem = (void*)0;
	int shmid;
	int *shmaddr;
	int i;

	// step0. ftok()

	// step1. shmget
    // shmget 은 공유하기 위한 메모리를 확보하는 함수로, key값에 맞는 공간이 없으면
    // 새로운 물리 공간을 생성하고, 있는 경우 그 id를 가져온다.
	shmid = shmget((key_t)1234, sizeof(int)*SHMSIZE, 0666 | IPC_CREAT);
	if (shmid == -1)
	{
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	// step2. shmat
	shared_Mem = shmat(shmid, (void*)0, 0);
	if (shared_Mem == (void*)-1)
	{
        st
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}

	printf("Memory attached at %X\n", (int)shared_Mem);
	shmaddr = (int*)shared_Mem;

	// step3. memory access
	for (i = 0; i < SHMSIZE; i++)
	{
		printf("shmaddr:%X, data:%d\n", shmaddr + i, *(shmaddr + i));
	}

	//sleep(4);
	
	// step4. shmdt
	if (shmdt(shared_Mem) == -1)
	{
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	
	// step5. shmctl : IPC_RMID
	if (shmctl(shmid, IPC_RMID, 0) == -1)
	{
		fprintf(stderr, "shmctl (IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
}