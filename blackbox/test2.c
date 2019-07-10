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



// #define DEBUG
//	#include "debug_message.h"
// #ifdef DEBUG    // DEBUG?? ?????? ???? debug_message.h ??? ???? ????
// #include "message.h"
// #else           // ???? message.h ??? ???? ????
// #endif

#define size 256
#define event_dir "./event"
#define always_dir "./always"
#define max_len 256	
#define pt "/home/jiwoong/objectDetection/blackbox/del_dir/"
int indent = 0;
int dir_size = 0;
struct f_size
{
	long blocks;
	long avail;
	long avail_per;
};

float avail()
{
	char buf[size];
	char null[16];
   char addr[size];
	float avail;
	int trans;
	struct statfs lstatfs;
   getcwd(addr, size);
   printf("%s\n", addr);
	if (statfs(addr, &lstatfs) == -1) {
		perror("statfs_error");
		return -1;
	}
	avail = ((float)lstatfs.f_bavail / (float)lstatfs.f_blocks) * 100;
	return avail;
}

int main(){
   float ava;
   ava = avail();
   printf("%f\n", ava);
}
