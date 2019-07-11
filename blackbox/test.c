#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //access
#include <libgen.h>
#include <errno.h>
#include <sys/vfs.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/time.h>


#define event_dir "./event"
#define always_dir "./always"
#define max_len 256	


void mkfrontdir()
{   
	int ret;
	char dir[256] = {0, };
	// char* dir2;
	strcpy(dir, event_dir);
	if (access(dir, 0) == 0)
	{
		printf("file exists");
		exit(1);
	}
	else
	{
		if((ret = mkdir(dir, 0755)) == -1)
		{
			fprintf(stderr, "error: %s\n", strerror(errno));
			exit(1);
		}
		printf("success making %s", dir);    
	}
}

int main(void){
	mkfrontdir();
	return 0;
}