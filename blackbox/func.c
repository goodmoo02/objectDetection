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

// ???? ????? ?? ???? ?? ?? ???.
int indent = 0;
int dir_size = 0;
struct f_size
{
	long blocks;
	long avail;
	long avail_per;
};

char* get_time(char* ch){
    time_t rawtime;
    struct tm *timeinfo;
	char* buffer = (char*)malloc(sizeof(char)*256);
    if ((timeinfo = localtime(&rawtime)) == NULL){
		printf("1");
	}
	if ((ch == "d") || (ch == "D"))		
        strftime(buffer, size, "%Y%m%d", timeinfo);
	else if ((ch == "h") || (ch == "H"))		
        strftime(buffer, size, "%Y%m%d_%H", timeinfo);
	else if ((ch == "s") || (ch == "S"))
		strftime(buffer, size, "%Y%m%d_%H%M%S", timeinfo);
	else
		return 0;
	
	return buffer;
}

void makedir(char* pos, char* time_type){
	char addr[size] = {0};
	getcwd(addr, size);
	char* time_buf;
	if ((time_buf = get_time(time_type)) == NULL){
		perror("get_time failed");
	}
	strcat(pos, time_buf);
	mkdir(pos, 0755);
}

// access ??? - ???? ???? ?? ???? ???
// R_OK : ???? ???? ????, ?¬Ò? ???? ????
// W_OK : ???? ???? ????, ???? ???? ????
// X_OK : ???? ???? ????, ???? ???? ????
// F_OK : ???? ???? ???? 

// 00 - ???? ?? ?????? ???? ????? ????
// 02 - ???? ?????? ??????? ????
// 04 - ?¬Ò? ?????? ??????? ????
// 06 - ?¬Ò? ?? ???? ??????? ????

//	char *pathname = "./hello.txt";
// 	int mode = R_OK | W_OK;
// 	if( access( pathname, mode ) == 0 )
// 		printf("?¬Ñ? ?? ?? ??????.");
// 	else
// 		printf("?????? ????? ???????? ??????.");


int mkeventdir()
{
	int ret;
	if (access(event_dir, 0) == 0)
		return 0;
	else
	{
		if((ret = mkdir(event_dir, 0755)) == -1)
            if(errno != EEXIST)
            {
                fprintf(stderr, "error: %s\n", strerror(errno));
                return -1;
            }
		printf("success making event_dir");
		return 0;
	}
}

int mkalwaysdir()
{
	int ret;
	if (access(always_dir, 0) == 0)
		return 0;
	else
	{
		if((ret = mkdir(always_dir, 0755)) == -1)
            if(errno != EEXIST)
            {
                fprintf(stderr, "error: %s\n", strerror(errno));
                return -1;
            }
		printf("success making always_dir");
		return 0;
	}
}


struct f_size* avail(char* dirname)
{
	char buf[256];
	char null[16];
	float avail;
	int trans;
	struct statfs lstatfs;
	struct f_size* lf_size;

	lf_size = (struct f_size*)malloc(sizeof(lf_size));
	if (statfs(dirname, &lstatfs) == -1) {
		perror("statfs_error");
		return NULL;
	}
	lf_size->blocks = lstatfs.f_blocks * (lstatfs.f_bsize / 1024);
	// ???? ????? ?? ?? ?????? ???? * ??????? ???? ???? ??? / 1024
	lf_size->avail = lstatfs.f_bavail * (lstatfs.f_bsize / 1024);
	// ??-???? ?????? ???? ???? ???? * ??????? ???? ???? ??? / 1024
	lf_size->avail_per = lstatfs.f_bavail / lstatfs.f_blocks;
	return lf_size;
}


int rm_olddir(char* dir){
    struct dirent **dir_list;
    struct dirent **f_list;
    // DIR *dir_info;
    int dir_count;
    int f_count;
    int idx;
    char dir_name[max_len] = { 0, };
    char f_name[max_len] = {0, };
    if((dir_count = scandir(dir, &dir_list, NULL, alphasort))==-1)
    {
        fprintf(stderr, "error: %s\n", strerror(errno));
        return -1;
    }
    printf("%s\n", "dir_scan_compelete");
    
    strcat(dir_name, pt);
    strcat(dir_name, dir_list[2]->d_name);

    if(rmdir(dir_name) == -1)
        {
            printf("dir has files..");
            if((f_count = scandir(dir_name, &f_list, NULL, alphasort))==-1)
            {
                fprintf(stderr, "error: %s\n", strerror(errno));
                return -1;
            }
            printf("%s\n", "file_scan_compelete");

            for (idx=2; idx < f_count; idx++){
                strcpy(f_name, dir_name);
                strcat(f_name, "/");
                strcat(f_name, f_list[idx]->d_name);
                printf("%s\n", f_name);
                if(remove(f_name) == -1)
                {
                    fprintf(stderr, "f_del_error: %s\n", strerror(errno));
                    return -1;
                }
            }

            printf("%s\n", "file_del_compelete");
            if(remove(dir_name) == -1)
                {
                    fprintf(stderr, "error: %s\n", strerror(errno));
                    return -1;
                }
            printf("%s\n", "dir_del_compelete");
            return 0;
        }
}