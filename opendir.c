#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
    DIR *dir_info;
    struct dirent *dir_entry;

    mkdir("makeA",0755);
    mkdir("makeB",0755);

    dir_info=opendir(".");

    if(NULL!=dir_info)
    {
        while(dir_entry=readdir(dir_info))
 // readdir()는 DIR *dir이 가리키는 디렉토리 내 파일 목록의 주소dirent를 반환하고, *dir의 다음 파일 목록을 가르킨다. 파일 목록은 readdir함수를 반복 호출해서 반환받은 구조체의 내용을 얻어내면 된다.
        {
            printf("%s\n", dir_entry->d_name); 
        }
        closedir(dir_info);
    }

}

