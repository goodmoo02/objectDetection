#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>

int glob_var = 6;


void *t_function(void *data)
{
    int id;
    pthread_t t_id;
    id = *((int *)data);
// pthread_t pthread_self(void)
    t_id=pthread_self();
    printf("pid=%d, t_id=%lu, id=%d, glob_var=%d\n",getpid(),t_id,id,glob_var);
    printf("pid=%d\n", syscall(__NR_gettid));
    return (void*)(id*id);
}

int main(void)
{
    pthread_t p_thread[2];
    int status;
    int a=1;
    int b=2;
    int err;

    printf("before pthread_create() pid = %d, glob_var=%d\n",getpid(), glob_var);
// int pthread_create(pthread_t* th , 쓰레드 특성(기본-NULL) , 함수포인터, 함수포인터 매개변수)
// th - 쓰레드 생성시 쓰레드 식별자 , 함수포인터는 함수포인터 매개변수와 함께 함수 작동함.
    //create thread1 
    if((err = pthread_create(&p_thread[0], NULL, t_function, (void*)&a)) <0)
    {
        perror("thread create error : ");
        exit(1);
    }

    //create thread2 
    if((err = pthread_create(&p_thread[1], NULL, t_function, (void*)&b)) <0)
    {
        perror("thread create error : ");
        exit(2);
    }
// int pthread_join(pthread_t th, void **thread_return);
// th - 종료되길 기다리는 thread  / thread_return - th 함수의 결과값을 저장할 공간
    pthread_join(p_thread[0], (void**)&status);
    printf("thread join : %d\n", status);

    pthread_join(p_thread[1], (void**)&status);
    printf("thread join : %d\n", status);

    printf("after pthread_create() glob_var=%d\n", glob_var);

    return 0;

}
