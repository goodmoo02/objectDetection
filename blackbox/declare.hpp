#include <opencv2/opencv.hpp>
#include <sstream>

#define event_dir "./event/"
#define always_dir "./always/"
#define max_len 256	
#define size 256

//int indent = 0;
//int dir_size1 = 0;

namespace patch
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}

struct f_size
{
	long blocks;
	long avail;
	long avail_per;
};

struct cap_dir{
    char* dir;
    cv::VideoCapture capp;
};


// 함수 선언
std::string get_tegra_pipeline(int, int, int);
void* mkfrontdir(void*);
char* gettime(char*);
int disp_runtime(struct timeval, struct timeval);
char* makedir(void*);
int rec(struct cap_dir);
void* mkdir_file(void*);
struct f_size* dir_info(char*);
float avail(void*);
int rm_olddir(char*);
void* auto_rmdir(void*);
