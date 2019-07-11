#include <opencv2/opencv.hpp>
#include <iostream>
#include "declare.hpp"
// char* get_time(char* ch);
// void makedir(char* pos, char* time_type);
// int mkfrontdir();
// struct f_size* avail(char* dirname);
// int rm_olddir(char* dir);

using namespace cv;
using namespace std;

int main(void)
{
    pthread_t p_thread[1];
    int err;
    
    // opencv options
    int WIDTH = 1920;
    int HEIGHT = 1080;
    int FPS = 30;
	

    // opencv 녹화 준비
    // Define the gstream pipeline
    /*
    std::string pipeline = get_tegra_pipeline(WIDTH, HEIGHT, FPS);
    std::cout << "Using pipeline: \n\t" << pipeline << "\n";
    // 비디오 캡쳐 초기화
    VideoCapture cap(pipeline, CAP_GSTREAMER);
    if (!cap.isOpened()) {
    cerr << "에러 - 카메라를 열 수 없습니다.\n";
    return -1;
    }
    // 동영상 파일을 저장하기 위한 준비
    Size size1 = Size((int)cap.get(CAP_PROP_FRAME_WIDTH),
      	(int)cap.get(CAP_PROP_FRAME_HEIGHT));

*/
    

// thread 관리
    
    // event, always dir 생성
    if((err = pthread_create(&p_thread[0], NULL, mkfrontdir, (void*)0)) <0)
    {
        perror("thread create error : ");
        exit(1);
    }
/*
    // always dir 내부의 날짜 dir 생성 및 녹화 시작
    if((err = pthread_create(&p_thread[1], NULL, mkdir_file,(void*)&cap)) <0)
    {
        perror("thread create error : ");
        exit(2);
    }

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
