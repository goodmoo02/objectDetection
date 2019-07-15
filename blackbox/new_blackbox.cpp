#include <opencv2/opencv.hpp>
#include <iostream>
#include "declare.hpp"


using namespace cv;
using namespace std;

int FLAG = 0;
int main(void)
{
	pthread_t p_thread[2];
	int err;
	int result = 1;
	
	if ((err = pthread_create(&p_thread[0], NULL, mkdir_file, (void*)0)) < 0)
	{
		perror("thread create error : ");
		exit(2);
	}

	if((err = pthread_create(&p_thread[1], NULL, auto_rmdir, (void*)0)) <0)
	{
		perror("thread create error : ");
		exit(3);
	}
	
	while(!FLAG)
		continue;

	pthread_detach(p_thread[0]);
	pthread_detach(p_thread[1]);
	return 0;
}
