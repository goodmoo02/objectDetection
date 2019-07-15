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


std::string get_tegra_pipeline(int width, int height, int fps) {
	return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + patch::to_string(width) + ", height=(int)" +
		patch::to_string(height) + ", format=(string)NV12, framerate=(fraction)" + patch::to_string(fps) +
		"/1 ! nvvidconv ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}


void* mkdir_file(void* voi)
{
	int WIDTH = 640;
	int HEIGHT = 480;
	int FPS = 30;

	std::string pipeline = get_tegra_pipeline(WIDTH, HEIGHT, FPS);
	std::cout << "Using pipeline: \n\t" << pipeline << "\n";

	VideoCapture cap(pipeline, CAP_GSTREAMER);

	if (!cap.isOpened()) {
		cerr << "error: VideoCapture not opened\n";
		exit(1);
	}

	while (1)
	{
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
			if (waitKey(25) >= 0)
				break;

			gettimeofday(&UTCtime_e, NULL);

			if (disp_runtime(UTCtime_s, UTCtime_e) == act_time) 
			{
				writer.release();
				break;
			}
		}
	}
	exit(0);
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

int main(void){
    mkdir_file((void*)0);
    return 0;
}