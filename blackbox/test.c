#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>  
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

void main()
{
	struct dirent *dentry;
	struct stat fstat;
	DIR *drip;
	dirp = opendir(".");
	while(dentry = readdir(dirp))
		printf("%s\n", dentry->d_name);
	closedir(dirp);

}	
