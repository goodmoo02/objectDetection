#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
//For IPC 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
    FILE* fp;
    FILE* fp2;
    char num[11];
    
    int i;
    int j;

    fp = fopen("test.txt", "rb");
    fp2 = fopen("test2.txt", "ab");
    i = fread(num, 1, 10, fp);
    j = fwrite(num, 1, 10, fp2);
    printf("%s, %d, %d", num, i, j);
}
    
