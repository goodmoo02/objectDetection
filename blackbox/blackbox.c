#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>


// 2. 현재 시간으로된 폴더를 생성한다.
//    ex) 20180530_09  년월일시까지 폴더이름 적용

// 3. 녹화를 시작하기전에 디스크 용량을 확인한다.
//    폴더는 /home/pi/user/blackbox로 한다.
//    용량이 부족한 경우 blackbox폴더의 하위 디렉토리중 가장 오래된
//    폴더를 삭제한다.  

// 4. 현재 시간으로된 녹화 파일을 생성한다.
//    ex) 20180530_091023.mpg 초까지 파일명에 적용
#define size 300
int main() {
    
    char ch;
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[size];
    char now_buffer[size];
    char encod[] = ".mpg";
    FILE *file_pointer;
    void makedir();
    void makefile();

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    makedir(buffer);
    makefile(buffer, encod);
    return 0;
}

void makedir(char* b){
    char addr[size] = "/home/jiwoong/user/blackbox/";
    char buffer[size];
    struct tm* timeinfo;
    time_t rawtime;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 300, "%Y%m%d_%H", timeinfo);

    strcat(addr, buffer);
    mkdir(addr, 0755);
    strcpy(b, addr);
}

void makefile(char* dir, char* encod){
    char buffer[size];
    char ch[] = "/";
    struct tm* timeinfo;
    time_t rawtime;
    FILE *file_pointer;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, size, "%Y%m%d_%H%M%S", timeinfo);
    strcat(dir, ch);
    strcat(dir, buffer);
    strcat(dir, encod);
    file_pointer=fopen(dir, "wb");
    fclose(file_pointer);
}