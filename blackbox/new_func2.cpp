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
#include "declare2.hpp"

using namespace cv;
using namespace std;

char* gettime(char* ch) {
	time_t rawtime;
	struct tm *timeinfo;
	char* buffer = (char*)malloc(sizeof(char) * size);
	time(&rawtime);
	if ((timeinfo = localtime(&rawtime)) == NULL)
	{
		printf("1");
	}
	if ((ch == "d") || (ch == "D"))
		strftime(buffer, size, "%Y%m%d/", timeinfo);
	else if ((ch == "h") || (ch == "H"))
		strftime(buffer, size, "%Y%m%d_%H/", timeinfo);
	else if ((ch == "m") || (ch == "M"))
		strftime(buffer, size, "%Y%m%d_%H%M", timeinfo);
	else if ((ch == "s") || (ch == "S"))
		strftime(buffer, size, "%Y%m%d_%H%M%S", timeinfo);
	else
		return 0;

	return buffer;
}



void* mkfrontdir(void* voi)
{
	int i;
	int ret;
	char dir[size] = { 0, };
	char dir2[size] = { 0, };
	strcpy(dir, event_dir);
	strcpy(dir2, always_dir);

	if (access(dir, 0) == 0)
		printf("event_dir exists\n");
	else
	{
		if ((ret = mkdir(dir, 0755)) == -1)
		{
			fprintf(stderr, "event_dir error: %s\n", strerror(errno));
			exit(1);
		}
		printf("success making %s\n", dir);
	}

	if (access(dir2, 0) == 0)
		printf("always_dir exists\n");
	else
	{
		if ((ret = mkdir(dir2, 0755)) == -1)
		{
			fprintf(stderr, "always_dir error: %s\n", strerror(errno));
			exit(1);
		}
		printf("success making %s\n", dir2);
	}
}



char* makedir(void* voi) {
	char* str_buf = (char*)malloc(sizeof(char)*size);
	char* time_buf;
	if ((time_buf = gettime("h")) == NULL) {
		perror("gettime failed");
		exit(1);
	}
	strcpy(str_buf, always_dir);
	strcat(str_buf, time_buf);
	mkdir(str_buf, 0755);
	return str_buf;
}


string get_tegra_pipeline(int width, int height, int fps) {
	return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + patch::to_string(width) + ", height=(int)" +
		patch::to_string(height) + ", format=(string)NV12, framerate=(fraction)" + patch::to_string(fps) +
		"/1 ! nvvidconv ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}


void* mkdir_file(void* voi)
{
	int i = 1;
	int* result = (int*) voi;

	while (i)
	{	
		pthread_mutex_lock(&mutex_lock);
		char addr[size] = { 0, };
		char* time_buf;
		char* dir_buf = makedir((void*)0);
		strcpy(addr, dir_buf);

		free(dir_buf);

		if ((time_buf = gettime("s")) == NULL)
			perror("gettime(sec) failed");
		strcat(addr, time_buf);
		strcat(addr, ".avi");
		printf("%s\n", addr);
		pthread_mutex_unlock(&mutex_lock);
	}
}


void* mkdir_file2(void* voi)
{
	int i = 1;
	int* result = (int*) voi;
	int WIDTH = 640;
	int HEIGHT = 480;
	int FPS = 30;

	while (i)
	{
		pthread_mutex_unlock(&mutex_lock);
		VideoWriter writer;
		Size size1 = Size((int)cap.get(CAP_PROP_FRAME_WIDTH), (int)cap.get(CAP_PROP_FRAME_HEIGHT));
		printf("width: %d, height: %d\n", (int)cap.get(CAP_PROP_FRAME_WIDTH), (int)cap.get(CAP_PROP_FRAME_WIDTH));
		double fps = 30.0;

		writer.open(addr, VideoWriter::fourcc('D', 'I', 'V', 'X'), fps, size1, true);
		

		if (!writer.isOpened())
		{
			cout << "error: writer.open failed\n" << endl;
			exit(0);
		}

		Mat img_color;

		struct timeval UTCtime_s, UTCtime_e;
		
		gettimeofday(&UTCtime_s, NULL);
		while (1)
		{
			cap.read(img_color);
			if (img_color.empty())
			{
				cerr << "error: empty frame\n";
				break;
			}
			writer.write(img_color);

			imshow("Color", img_color);
			if (waitKey(10) >= 0){
				i = 0;
				writer.release();
				break;	
			}
				
			gettimeofday(&UTCtime_e, NULL);

			if (disp_runtime(UTCtime_s, UTCtime_e) == act_time) 
			{
				writer.release();
				break;
			}
		}
	}
	destroyAllWindows();
	FLAG = 1;
	*result = 0;
}




int disp_runtime(struct timeval UTCtime_s, struct timeval UTCtime_e)
{
	struct timeval UTCtime_r;
	if ((UTCtime_e.tv_usec - UTCtime_s.tv_usec) < 0)
	{
		UTCtime_r.tv_sec = UTCtime_e.tv_sec - UTCtime_s.tv_sec - 1;
		//UTCtime_r.tv_usec = 1000000 - UTCtime_e.tv_usec - UTCtime_s.tv_usec;
	}
	else
	{
		UTCtime_r.tv_sec = UTCtime_e.tv_sec - UTCtime_s.tv_sec;
		//UTCtime_r.tv_usec = UTCtime_e.tv_usec - UTCtime_s.tv_usec;
	}
	return UTCtime_r.tv_sec;
}


void* auto_rmdir(void* result)
{
	//int* res = (int*) result;
	float ava;
	while (!FLAG){

		ava = avail((void*)0);
		if (ava < 30) {
			rm_olddir((char*)always_dir);
			printf("delete old dir");
		}
		else {
			printf("no");
		}

		sleep(act_time);
	}
	
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


int rm_olddir(char* dir) {
	struct dirent **dir_list;
	struct dirent **f_list;
	// DIR *dir_info;
	int dir_count;
	int f_count;
	int idx;
	char dir_name[max_len] = { 0, };
	char f_name[max_len] = { 0, };
	
	if ((dir_count = scandir(dir, &dir_list, NULL, alphasort)) == -1)
	{
		fprintf(stderr, "error: %s\n", strerror(errno));
		return -1;
	}
	printf("%s\n", "dir_scan_compelete");

	strcat(dir_name, always_dir);
	strcat(dir_name, dir_list[2]->d_name);


	if (rmdir(dir_name) == -1)
	{
		printf("dir has files..");

		if ((f_count = scandir(dir_name, &f_list, NULL, alphasort)) == -1)
		{
			fprintf(stderr, "error: %s\n", strerror(errno));
			return -1;
		}
		printf("%s\n", "file_scan_compelete");

		for (idx = 2; idx < f_count; idx++) {
			strcpy(f_name, dir_name);
			strcat(f_name, "/");
			strcat(f_name, f_list[idx]->d_name);
			printf("%s\n", f_name);
			if (remove(f_name) == -1)
			{
				fprintf(stderr, "f_del_error: %s\n", strerror(errno));
				return -1;
			}
			free(f_list[idx]);
		}
		free(f_list);
		printf("%s\n", "file_del_compelete");

		if (remove(dir_name) == -1)
		{
			fprintf(stderr, "error: %s\n", strerror(errno));
			return -1;
		}
		printf("%s\n", "dir_del_compelete");
		
		for (idx = 0; idx < dir_count; idx++)
			free(dir_list[idx]);
		free(dir_list);
		return 0;
	}
}

//int main(void){
//	mkdir_file((void*)0);
//	return 0;
//}

