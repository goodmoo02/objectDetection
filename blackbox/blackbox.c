#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>


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
