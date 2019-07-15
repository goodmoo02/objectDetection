#include <opencv2/opencv.hpp>
#include <sstream>

#define event_dir "./event/"
#define always_dir "./always/"
#define max_len 256	
#define size 256
#define act_time 60


namespace patch
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}

class Cvcap{
	private:
		VideoCapture cap;
	public:
		VideoCapture cap(pipeline, CAP_GSTREAMER);
};

// 함수 선언
std::string get_tegra_pipeline(int, int, int);
void* mkfrontdir(void*);
char* gettime(char*);
int disp_runtime(struct timeval, struct timeval);
char* makedir(void*);
void* mkdir_file(void*);
float avail(void*);
int rm_olddir(char*);
void* auto_rmdir(void*);

extern int FLAG;	
extern pthread_mutex_t mutex_lock;