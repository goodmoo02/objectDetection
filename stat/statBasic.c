#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stat_size(char* dir){
	struct stat sb;
	float c1, c2;
	stat(dir, &sb);
	c1 = sb.st_blksize * sb.st_blocks ;
	c2 = sb.st_size;
	printf("%f\n, %f\n", c1, c2);
}
int main(){
	// struct stat statbuf;
	char *dirname = ".";
//	strcpy(dirname, ".");
	stat_size(dirname);
}
