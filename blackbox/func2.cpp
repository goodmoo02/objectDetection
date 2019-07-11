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
#include "declare.hpp"

using namespace cv;
using namespace std;

void* mkfrontdir(void* voi)
{   
	int i;
	int ret;
	char dir[size] = {0, };
	char dir2[size] = {0, };
	strcpy(dir, event_dir);
	strcpy(dir2, always_dir);
	if (access(dir, 0) == 0)
		printf("event_dir exists\n");
	else
	{
		if((ret = mkdir(dir, 0755)) == -1)
		{
			fprintf(stderr, "error: %s\n", strerror(errno));
			exit(1);
		}
		printf("success making %s\n", dir);    
	}
	if (access(dir2, 0) == 0)
	{
		printf("always_dir exists\n");
	}
	else
	{
		if((ret = mkdir(dir2, 0755)) == -1)
		{
			if(errno != EEXIST)
			{
				fprintf(stderr, "error: %s\n", strerror(errno));
				exit(1);				}
		}
		printf("success making %s\n", dir2);    
	}
	exit(0);
}

// ???? ????? ?? ???? ?? ?? ???.

char* gettime(char* ch){
	time_t rawtime;
	struct tm *timeinfo;
	char* buffer = (char*)malloc(sizeof(char)*256);
	time(&rawtime);
	if ((timeinfo = localtime(&rawtime)) == NULL)
	{
		printf("1");
		}
		if ((ch == "d") || (ch == "D"))		
		strftime(buffer, size, "%Y%m%d/", timeinfo);
		else if ((ch == "h") || (ch == "H"))		
		strftime(buffer, size, "%Y%m%d_%H/", timeinfo);
		else if ((ch == "s") || (ch == "S"))
			strftime(buffer, size, "%Y%m%d_%H%M%S", timeinfo);
		else
			return 0;
		
		return buffer;
	}

	int disp_runtime(struct timeval UTCtime_s, struct timeval UTCtime_e)
	{
		struct timeval UTCtime_r;
		if((UTCtime_e.tv_usec- UTCtime_s.tv_usec)<0)
		{
			UTCtime_r.tv_sec  = UTCtime_e.tv_sec - UTCtime_s.tv_sec - 1;
			UTCtime_r.tv_usec = 1000000 - UTCtime_e.tv_usec - UTCtime_s.tv_usec;
		}
		else
		{
			UTCtime_r.tv_sec = UTCtime_e.tv_sec - UTCtime_s.tv_sec;
			UTCtime_r.tv_usec = UTCtime_e.tv_usec - UTCtime_s.tv_usec;
		}
		return UTCtime_r.tv_sec;
	}

char* makedir(void* voi){
	char* str_buf  = (char*)malloc(sizeof(char)*size); 
	char* time_buf;
	char* ch = "h";
	if ((time_buf = gettime(ch)) == NULL){
		perror("gettime failed");
		exit(1);
	}
		strcpy(str_buf, always_dir);
		strcat(str_buf, time_buf);
		mkdir(str_buf, 0755);
	return str_buf;
}

std::string get_tegra_pipeline(int width, int height, int fps) {
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + patch::to_string(width) + ", height=(int)" + 
	patch::to_string(height) + ", format=(string)NV12, framerate=(fraction)" + patch::to_string(fps) +
            "/1 ! nvvidconv ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

// int rec(struct cap_dir* cd)
// {
// 	VideoWriter writer;
// 	// 동영상 파일을 저장하기 위한 준비
// 	Size size1 = Size((int)cd->capp->get(CAP_PROP_FRAME_WIDTH),(int)cd->capp->get(CAP_PROP_FRAME_HEIGHT));
//     double fps = 30.0;
// 	writer.open(cd->dir, VideoWriter::fourcc('D', 'I', 'V', 'X'), fps, size1, true);
// 	if (!writer.isOpened())
// 	{
// 		cout << "동영상을 저장하기 위한 초기화 작업 중 에러 발생" << endl;
// 		return 1;
// 	}

//     Mat img_color;

//     struct timeval UTCtime_s, UTCtime_e;
//     int act_time;
//     gettimeofday(&UTCtime_s, NULL);
// 	while(1)
// 	{
// 		cd->capp->read(img_color);
// 		if (img_color.empty()) {
// 			cerr << "빈 영상이 캡쳐되었습니다.\n";
// 			break;
// 		}

// 		//동영상 파일에 한 프레임을 저장함.  
// 		writer.write(img_color);

// 		imshow("Color", img_color);
//         if (waitKey(25) >= 0)
// 			break;
//         gettimeofday(&UTCtime_e, NULL);
        
//         if((act_time = disp_runtime(UTCtime_s, UTCtime_e))== 10)
//             break;
// 	}
// 	return 0;
// }

void* mkdir_file(void* cap)
{
	while(1)
	{
        	char addr[size] = {0, };
        	char* time_buf;
		char* str_buf = makedir((void*)0);
		VideoCapture cap1 = *(VideoCapture*)cap;
		
	        strcpy(addr, str_buf);
		free(str_buf);
		if ((time_buf = gettime("s")) == NULL)
			perror("gettime failed");
        	strcat(addr, time_buf);
        	strcat(addr, ".avi");
		
		VideoWriter writer;
		// 동영상 파일을 저장하기 위한 준비
		Size size1 = Size((int)cap1.get(CAP_PROP_FRAME_WIDTH),(int)cap1.get(CAP_PROP_FRAME_HEIGHT));
		printf("%d\n", (int)cap1.get(CAP_PROP_FRAME_WIDTH));
    		double fps = 30.0;
		printf("%s\n", addr);
		writer.open(addr, VideoWriter::fourcc('D', 'I', 'V', 'X'), fps, size1, true);

		if (!writer.isOpened())
		{
			cout << "동영상을 저장하기 위한 초기화 작업 중 에러 발생" << endl;
			exit(0);
		}

    	Mat img_color;

    	struct timeval UTCtime_s, UTCtime_e;
    	int act_time;
    	gettimeofday(&UTCtime_s, NULL);
	while(1)
	{
		cap1.read(img_color);
		if (img_color.empty()) 
		{
			cerr << "빈 영상이 캡쳐되었습니다.\n";
			break;
		}

		//동영상 파일에 한 프레임을 저장함.  
		writer.write(img_color);

		imshow("Color", img_color);
        	if (waitKey(25) >= 0)
			break;
        	gettimeofday(&UTCtime_e, NULL);
        
        	if((act_time = disp_runtime(UTCtime_s, UTCtime_e))== 10)
            		break;
	}
	
	}
	exit(0);
}


// access ??? - ???? ???? ?? ???? ???
// R_OK : ???? ???? ????, ?��? ???? ????
// W_OK : ???? ???? ????, ???? ???? ????
// X_OK : ???? ???? ????, ???? ???? ????
// F_OK : ???? ???? ???? 

// 00 - ???? ?? ?????? ???? ????? ????
// 02 - ???? ?????? ??????? ????
// 04 - ?��? ?????? ??????? ????
// 06 - ?��? ?? ???? ??????? ????

//	char *pathname = "./hello.txt";
// 	int mode = R_OK | W_OK;
// 	if( access( pathname, mode ) == 0 )
// 		printf("?��? ?? ?? ??????.");
// 	else
// 		printf("?????? ????? ???????? ??????.");



struct f_size* dir_info(char* dirname)
{
	float avail;
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

float avail(void* voi)
{
    char addr[size] = { 0, };
	float avail;
	struct statfs lstatfs;
    getcwd(addr, size);
	if (statfs(addr, &lstatfs) == -1) {
		perror("statfs_error");
		return -1;
	}
	avail = ((float)lstatfs.f_bavail / (float)lstatfs.f_blocks) * 100;
	return avail;
}

int rm_olddir(char* dir){
    struct dirent **dir_list;
    struct dirent **f_list;
    // DIR *dir_info;
    int dir_count;
    int f_count;
    int idx;
    char dir_name[max_len] = { 0, };
    char f_name[max_len] = { 0, };
    if((dir_count = scandir(dir, &dir_list, NULL, alphasort))==-1)
    {
        fprintf(stderr, "error: %s\n", strerror(errno));
        return -1;
    }
    printf("%s\n", "dir_scan_compelete");
    
    strcat(dir_name, always_dir);
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

void* auto_rmdir(void* voi)
{
    float ava;
    while(1)
        ava = avail((void*)0);
        if (ava > 80){
            rm_olddir((char*)always_dir);
            printf("용량초과로 삭제");
        }
        else{
            printf("용량 충분");
        }
        sleep(10);
}
