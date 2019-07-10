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
#include <opencv2/opencv.hpp>
#include <iostream>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/time.h>

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

struct cap_dir{
    char* dir;
    VideoCapture cap;  
};

using namespace cv;
using namespace std;


// 함수 선언
std::string get_tegra_pipeline(int width, int height, int fps);
void mkfrontdir(void*);
char* get_time(char*);
int disp_runtime(struct timeval UTCtime_s, struct timeval UTCtime_e);
char* makedir(void);
int rec(struct cap_dir cd);
void mkdir_file(VideoCapture cap);
struct f_size* dir_info(char*);
float avail(void);
int rm_olddir(char*);
void auto_rmdir(void);
