#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
//For IPC 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

#define SIZE 4096
void *shared_Mem = (void*)0;
int shmid;
FILE *fp;
int pid;
struct info{
    char story[SIZE];
    int w_pid;
    int r_pid;
    int last;
};

struct info *inform;

void sig_handler(){
    if ((inform->last = fread(shared_Mem, 1, SIZE, fp)) != SIZE)
    {
        kill(pid, SIGINT);
        fclose(fp);
    }
    else
        kill(pid, SIGUSR1);
        printf("i'm reading\n");
}
void sig_handler2(){
    // step4. shmdt
	if (shmdt(shared_Mem) == -1)
	{
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}

int main()
{
	// step0. ftok()

	// step1. shmget
    // shmget 은 공유하기 위한 메모리를 확보하는 함수로, key값에 맞는 공간이 없으면
    // 새로운 물리 공간을 생성하고, 있는 경우 그 id를 가져온다.
    int shmSize;
    printf("w_wait");
    shmSize=sizeof(struct info);
	shmid = shmget((key_t)1234, shmSize, 0666 | IPC_CREAT);
	if (shmid == -1)
	{
        fprintf(stderr, "error: %s\n", strerror(errno));
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	// step2. shmat
	shared_Mem = shmat(shmid, (void*)0, 0);
	if (shared_Mem == (void*)-1)
	{
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}
    
    inform = (struct info*)shared_Mem;
	// printf("Memory attached at %X\n", (int)shared_Mem);

	// step3. memory access
    inform->w_pid = getpid();
    while((pid = inform->r_pid) == NULL)
    {
        sleep(1);
    }
        
    
    fp = fopen("index.jpeg", "rb");
    
    kill(getpid(), SIGUSR2);
    signal(SIGUSR2, sig_handler);
    signal(SIGINT, sig_handler2);
}