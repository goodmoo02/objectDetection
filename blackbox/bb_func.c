#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> //access
#include <stdlib.h>
#include <errno.h>
	
// #define DEBUG
//	#include "debug_message.h"
// #ifdef DEBUG    // DEBUG가 정의되어 있다면 debug_message.h 헤더 파일 포함
// #include "message.h"
// #else           // 아니면 message.h 헤더 파일 포함
// #endif

#define size 256
#define event_dir "./event"
#define always_dir "./always"

char* get_time(char* ch){
    time_t rawtime;
    struct tm *timeinfo;
	char* buffer = (char*)malloc(sizeof(char)*256);
    if ((timeinfo = localtime(&rawtime)) == NULL){
		printf("1");
	}
	if ((ch == "d") || (ch == "D"))		
        strftime(buffer, size, "%Y%m%d", timeinfo);
	else if ((ch == "h") || (ch == "H"))		
        strftime(buffer, size, "%Y%m%d_%H", timeinfo);
	else if ((ch == "s") || (ch == "S"))
		strftime(buffer, size, "%Y%m%d_%H%M%S", timeinfo);
	else
		return 0;
	
	return buffer;
}

void makedir(char* pos, char* time_type){
	char addr[size] = {0};
	getcwd(addr, size);
	char* time_buf;
	if ((time_buf = get_time(time_type)) == NULL){
		perror("get_time failed");
	}
	strcat(pos, time_buf);
	mkdir(pos, 0755);
}

// access 함수 - 디렉토리 유무 및 권한 확인
// R_OK : 파일 존재 여부, 읽기 권한 여부
// W_OK : 파일 존재 여부, 쓰기 권한 여부
// X_OK : 파일 존재 여부, 실행 권한 여부
// F_OK : 파일 존재 여부 

// 00 - 파일 및 디렉토리가 존재 하는지 조사
// 02 - 쓰기 접근이 허용되는지 조사
// 04 - 읽기 접근이 허용되는지 조사
// 06 - 읽기 및 쓰기가 허용되는지 조사

//	char *pathname = "./hello.txt";
// 	int mode = R_OK | W_OK;
// 	if( access( pathname, mode ) == 0 )
// 		printf("읽고 쓸 수 있습니다.");
// 	else
// 		printf("권한이 없거나 존재하지 않습니다.");


int mkeventdir()
{
	int ret;
	if (access(event_dir, 0) == 0)
		return 0;
	else
	{
		if((ret = mkdir(event_dir, 0755)) == -1)
            if(errno != EEXIST)
            {
                fprintf(stderr, "error: %s\n", strerror(errno));
                return -1;
            }
		printf("success making event_dir");
		return 0;
	}
}

int mkalwaysdir()
{
	int ret;
	if (access(always_dir, 0) == 0)
		return 0;
	else
	{
		if((ret = mkdir(always_dir, 0755)) == -1)
            if(errno != EEXIST)
            {
                fprintf(stderr, "error: %s\n", strerror(errno));
                return -1;
            }
		printf("success making always_dir");
		return 0;
	}
}


//int mk



void main(){
	int num1 = mkeventdir();
	int num2 = mkalwaysdir();
	printf("%d\n", num1);
	printf("%d\n", num2);
}



	
