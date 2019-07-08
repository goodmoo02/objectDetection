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
    fwrite(inform -> story, 1, inform->last, fp);
    kill(pid, SIGUSR2);
    printf("i'm copying\n");
}

void sig_handler2(){
    fclose(fp);
    kill(pid, SIGINT);
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

int main()
{
    
	// step0. ftok()

	// step1. shmget
    // shmget �� �����ϱ� ���� �޸𸮸� Ȯ���ϴ� �Լ���, key���� �´� ������ ������
    // ���ο� ���� ������ �����ϰ�, �ִ� ��� �� id�� �����´�.
	int shmSize;
	shmSize = sizeof(struct info);
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
    inform->r_pid = getpid();
    while((pid = inform->w_pid) == NULL)
        sleep(1);
    fp = fopen("test.jpeg", "ab");
	printf("r_wait");
    signal(SIGUSR1, sig_handler);
    signal(SIGINT, sig_handler2);
}