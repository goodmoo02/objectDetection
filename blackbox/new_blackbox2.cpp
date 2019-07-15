#include <opencv2/opencv.hpp>
#include <iostream>
#include "declare2.hpp"


using namespace cv;
using namespace std;

int FLAG = 0;
pthread_mutex_t mutex_lock;

int main(void)
{
	pthread_t p_thread[3];
	int err;
	int status;
	int result = 1;

	int WIDTH = 640;
	int HEIGHT = 480;
	int FPS = 30;
	string pipeline = get_tegra_pipeline(WIDTH, HEIGHT, FPS);
	Cvcap cap(pipeline);

	if ((err = pthread_create(&p_thread[0], NULL, mkfrontdir, (void*)0)) < 0)
	{
		perror("thread create error : ");
		exit(2);
	}
	pthread_join(p_thread[0], (void **)&status);


	
	if((err = pthread_create(&p_thread[1], NULL, auto_rmdir, (void*)0)) <0)
	{
		perror("thread create error : ");
		exit(3);
	}



	pthread_mutex_init(&mutex_lock, NULL);
	
	if ((err = pthread_create(&p_thread[2], NULL, mkdir_file, &)) < 0)
	{
		perror("thread create error : ");
		exit(2);
	}

		if ((err = pthread_create(&p_thread[3], NULL, mkdir_file2, &result)) < 0)
	{
		perror("thread create error : ");
		exit(2);
	}

	while(result)
		continue;

	pthread_detach(p_thread[0]);
	pthread_detach(p_thread[1]);
	return 0;
}
