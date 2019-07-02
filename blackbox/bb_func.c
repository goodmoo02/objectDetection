#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> //access
#include <stdlib.h>
#include <errno.h>
	
// #define DEBUG
//	#include "debug_message.h"
// #ifdef DEBUG    // DEBUG�� ���ǵǾ� �ִٸ� debug_message.h ��� ���� ����
// #include "message.h"
// #else           // �ƴϸ� message.h ��� ���� ����
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

// access �Լ� - ���丮 ���� �� ���� Ȯ��
// R_OK : ���� ���� ����, �б� ���� ����
// W_OK : ���� ���� ����, ���� ���� ����
// X_OK : ���� ���� ����, ���� ���� ����
// F_OK : ���� ���� ���� 

// 00 - ���� �� ���丮�� ���� �ϴ��� ����
// 02 - ���� ������ ���Ǵ��� ����
// 04 - �б� ������ ���Ǵ��� ����
// 06 - �б� �� ���Ⱑ ���Ǵ��� ����

//	char *pathname = "./hello.txt";
// 	int mode = R_OK | W_OK;
// 	if( access( pathname, mode ) == 0 )
// 		printf("�а� �� �� �ֽ��ϴ�.");
// 	else
// 		printf("������ ���ų� �������� �ʽ��ϴ�.");


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



	
