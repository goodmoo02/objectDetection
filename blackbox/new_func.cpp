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


// 실시간 가져오기 (날짜(d), 시간(h), 초(s) 단위까지 설정)
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


// 상위 폴더(event, always) 생성 (존재 확인 후 생성)
void* mkfrontdir(void* voi)
{
	int i;
	int ret;
	char dir[size] = { 0, };
	char dir2[size] = { 0, };
	strcpy(dir, event_dir);
	strcpy(dir2, always_dir);
	// event dir 존재 확인 후 생성
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
	// always dir 존재 확인 후 생성
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
	exit(0);
}


// 하위 폴더(시간(h)을 이름으로 하는 폴더) 생성
char* makedir(void* voi) {
	// 하위 폴더까지의 상대 위치를 문자열로 반환하기 위해 malloc 실시. (free 필요)
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


// tx2 board에서 VideoCapture에 첫번째 인자로 제공할 pipeline 반환
std::string get_tegra_pipeline(int width, int height, int fps) {
	return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + patch::to_string(width) + ", height=(int)" +
		patch::to_string(height) + ", format=(string)NV12, framerate=(fraction)" + patch::to_string(fps) +
		"/1 ! nvvidconv ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}



// 하위 폴더에 녹화파일 생성
void* mkdir_file(void* cap)
{
	VideoCapture cap1 = *(VideoCapture*)cap;
	while (1)
	{
		char addr[size] = { 0, };
		char* time_buf;
		
		// 하위폴더 생성 및 상대경로 반환 
		char* dir_buf = makedir((void*)0);
		
		strcpy(addr, dir_buf);

		// makedir에서 반환한 문자열 heap 해제
		free(dir_buf);

		// 상대경로의 파일 이름 및 확장자 설정
		if ((time_buf = gettime("s")) == NULL)
			perror("gettime(sec) failed");
		strcat(addr, time_buf);
		strcat(addr, ".avi");
		printf("%s\n", addr);
		// 동영상 파일을 저장하기 위한 준비
		VideoWriter writer;
		Size size1 = Size((int)cap1.get(CAP_PROP_FRAME_WIDTH), (int)cap1.get(CAP_PROP_FRAME_HEIGHT));
		printf("width: %d, height: %d\n", (int)cap1.get(CAP_PROP_FRAME_WIDTH), (int)cap1.get(CAP_PROP_FRAME_WIDTH));
		double fps = 30.0;

		// VideoWriter.open(const String &filename, int fourcc, double fps, Size frameSize, bool isColor=true)
		writer.open(addr, VideoWriter::fourcc('D', 'I', 'V', 'X'), fps, size1, true);
		
		// VideoWriter.isOpened() - 성공적으로 초기화가 되었는지 확인하는 메서드
		// 성공시 true 값 반환 / 
		if (!writer.isOpened()) // false 반환시(성공시) true가 되어 not open 출력
		{
			cout << "error: writer.open failed\n" << endl;
			exit(0);
		}

		Mat img_color;

		struct timeval UTCtime_s, UTCtime_e;
		
		// 시작시간 가져오기
		gettimeofday(&UTCtime_s, NULL);

		// VideoCaputure로부터 frame 가져오기 및 저장하기
		while (1)
		{
			// VideoCapture.read(frame) - capture한 image를 frame에 저장.
			cap1.read(img_color);
			if (img_color.empty())
			{
				cerr << "error: empty frame\n";
				break;
			}

			//VideoWriter.write(frame) - VideoWriter.open한 동영상 파일에 frame을 저장.  
			writer.write(img_color);
			// 하나의 frame을 window에 보여줌.
			imshow("Color", img_color);
			if (waitKey(25) >= 0)
				break;
			// 끝시간 가져오기
			gettimeofday(&UTCtime_e, NULL);

			// 녹화시간 = 끝시간 - 시작시간 하여 설정
			if (disp_runtime(UTCtime_s, UTCtime_e) == act_time) 
			{
				writer.release();
				break;
			}
		}
	}
	exit(0);
}
//int rec(struct cap_dir);
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

// 전체 용량 체크 후, 오래된 폴더부터 파일과 함께 삭제
//struct f_size* dir_info(char*);
void* auto_rmdir(void* voi)
{
	float ava;
	while (1){
		// 용량 확인
		ava = avail((void*)0);
		if (ava > 80) {
			// 폴더 및 파일 삭제
			rm_olddir((char*)always_dir);
			printf("용량초과로 삭제");
		}
		else {
			printf("용량 충분");
		}
		// 녹화시간에 비슷하게 틈을 주고 확인
		sleep(act_time);
	}
	
}

// 사용 용량 체크 및 반환
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

// 오래된 폴더 및 파일 삭제
int rm_olddir(char* dir) {
	struct dirent **dir_list;
	struct dirent **f_list;
	// DIR *dir_info;
	int dir_count;
	int f_count;
	int idx;
	char dir_name[max_len] = { 0, };
	char f_name[max_len] = { 0, };

	// always_dir의 하위 폴더 목록 추출
	if ((dir_count = scandir(dir, &dir_list, NULL, alphasort)) == -1)
	{
		fprintf(stderr, "error: %s\n", strerror(errno));
		return -1;
	}
	printf("%s\n", "dir_scan_compelete");

	strcat(dir_name, always_dir);
	strcat(dir_name, dir_list[2]->d_name);

	// 제일 오래된 폴더 삭제
	if (rmdir(dir_name) == -1) // fail 시 file 있는 것으로 간주.
	{
		printf("dir has files..");
		// 파일 삭제
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
		}

		printf("%s\n", "file_del_compelete");
		// 파일삭제 후 폴더 삭제
		if (remove(dir_name) == -1)
		{
			fprintf(stderr, "error: %s\n", strerror(errno));
			return -1;
		}
		printf("%s\n", "dir_del_compelete");
		return 0;
	}
}



