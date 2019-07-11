
//// �ǽð� �������� (�ð�(h), ��(m), ��(s) �������� ����)
//char* gettime(char*);
//
//// ���� ����(event, always) ���� (���� Ȯ�� �� ����)
//void* mkfrontdir(void*);
//
//// ���� ����(�ð�(h)�� �̸����� �ϴ� ����) ����
//char* makedir(void*);
//
//// ���� ������ ��ȭ���� ����
//std::string get_tegra_pipeline(int, int, int);
//void* mkdir_file(void*);
//int rec(struct cap_dir);
//int disp_runtime(struct timeval, struct timeval);
//
//// ��ü �뷮 üũ ��, ������ �������� ���ϰ� �Բ� ����
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


	// opencv ��ȭ �غ�
	// Define the gstream pipeline

	// VideoCapture�� ����� pipeline ����
	std::string pipeline = get_tegra_pipeline(WIDTH, HEIGHT, FPS);
	std::cout << "Using pipeline: \n\t" << pipeline << "\n";

	// ���� ĸ�� �ʱ�ȭ
	VideoCapture cap(pipeline, CAP_GSTREAMER);

	// VideoCapture �ʱ�ȭ �� open Ȯ��
	if (!cap.isOpened()) {
		cerr << "error: VideoCapture not opened\n";
		return -1;
	}


	// thread ����

	// event, always dir ����
	if ((err = pthread_create(&p_thread[0], NULL, mkfrontdir, (void*)0)) < 0)
	{
		perror("thread create error : ");
		exit(1);
	}
	
	// always dir ������ ��¥ dir ���� �� ��ȭ ����
	if ((err = pthread_create(&p_thread[1], NULL, mkdir_file, (void*)&cap)) < 0)
	{
		perror("thread create error : ");
		exit(2);
	}
	/*
		// ��� �뷮 Ȯ�� �� always dir�� old dir ����
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
