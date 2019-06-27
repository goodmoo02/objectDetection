#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(){
	setenv("MYDIR", "/home/js", 0);
	setenv("j_git", "/home/js/jiwoong/objectDetection", 0);
	setenv("KERNEL_SRC","usr/src/linux", 0);
	
	printf("MYDIR = %s\n", getenv("MYDIR"));
	printf("j_git = %s\n", getenv("j_git"));
	printf("KERNEL_SRC = %s\n", getenv("KERNEL_SRC"));
	
	while(*environ)
		printf("%s\n", *environ++);
	return 0;
}
