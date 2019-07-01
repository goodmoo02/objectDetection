#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int glob_var = 6;

void *f_function(void * data)
{
	int id;
	int i = 0;
	pthread_t t_id;
	id = *((int *)data);
	
	printf("pid=%d, t_is=%lu, id=%d, glob_var = %d\n", getpid(), t_id, id, glob_var);
	return (void *)(id * id);
}
int main(void)
{
	pthread_t p_thread[2];
	int status;
	int a=1;
	int b=2;
	int err;	

	printf("before pthread_cread() pid = %d, glob_var = %d\n", getpid(), glob_var);
	//create thread1
	
	if ((err = pthread_create(&p_thread[0], NULL, t_function, (void*)&a)) < 0)
	{
		perror("thread create error : ");
		exit(1);
	}

	//create thread2
	
	if (err = pthread_create(&p_thread[0], NULL, t_function, (void*)&a)) < 0)
	{
		perror("thread create error : ");
		exit(2);
	}
	
	pthread_join(p_thread[0], (void**)&status);
	printf("thread join : %s\n", status);

	pthread_join(p_thread[1], (void**)&status);
	printf("thread join : %s\n", status);

	printf("after pthread_create() glob_var = %d\n", glob_var);

	return 0;
}
