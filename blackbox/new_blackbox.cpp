
//// 실시간 가져오기 (시간(h), 분(m), 초(s) 단위까지 설정)
//char* gettime(char*);
//
//// 상위 폴더(event, always) 생성 (존재 확인 후 생성)
//void* mkfrontdir(void*);
//
//// 하위 폴더(시간(h)을 이름으로 하는 폴더) 생성
//char* makedir(void*);
//
//// 하위 폴더에 녹화파일 생성
//std::string get_tegra_pipeline(int, int, int);
//void* mkdir_file(void*);
//int rec(struct cap_dir);
//int disp_runtime(struct timeval, struct timeval);
//
//// 전체 용량 체크 후, 오래된 폴더부터 파일과 함께 삭제
////struct f_size* dir_info(char*);
//void* auto_rmdir(void*);
//float avail(void*);
//int rm_olddir(char*);

#include <opencv2/opencv.hpp>
#include <iostream>
#include "declare.hpp"


using namespace cv;
using namespace std;


int main(void)
{
	pthread_t p_thread[3];
	int err;

	// opencv options
	int WIDTH = 640;
	int HEIGHT = 480;
	int FPS = 30;


	// opencv 녹화 준비
	// Define the gstream pipeline

	// VideoCapture에 사용할 pipeline 생성
	std::string pipeline = get_tegra_pipeline(WIDTH, HEIGHT, FPS);
	std::cout << "Using pipeline: \n\t" << pipeline << "\n";

	// 비디오 캡쳐 초기화
	VideoCapture cap(pipeline, CAP_GSTREAMER);

	// VideoCapture 초기화 및 open 확인
	if (!cap.isOpened()) {
		cerr << "error: VideoCapture not opened\n";
		return -1;
	}


	// thread 관리

	// event, always dir 생성
	if ((err = pthread_create(&p_thread[0], NULL, mkfrontdir, (void*)0)) < 0)
	{
		perror("thread create error : ");
		exit(1);
	}
	
	// always dir 내부의 날짜 dir 생성 및 녹화 시작
	if ((err = pthread_create(&p_thread[1], NULL, mkdir_file, (void*)&cap)) < 0)
	{
		perror("thread create error : ");
		exit(2);
	}
	/*
		// 사용 용량 확인 후 always dir의 old dir 삭제
		if((err = pthread_create(&p_thread[2], NULL, auto_rmdir, (void*)0)) <0)
		{
			perror("thread create error : ");
			exit(3);
		}


		for(int i; i < 3; i++)
		{
			if ((err = pthread_detach(p_thread[i])) != 0)
			{
				perror("thread detach error :");
				exit(3);
			}
		}
	  */
	return 0;
}
