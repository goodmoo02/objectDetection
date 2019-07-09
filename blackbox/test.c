#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //access
#include <libgen.h>
#include <errno.h>
#include <sys/vfs.h>
#include <sys/stat.h>
#include <sys/types.h>

#define max_len 256
#define pt "/home/jiwoong/objectDetection/blackbox/del_dir/"
int rm_olddir(char* dir){
    struct dirent **dir_list;
    struct dirent **f_list;
    // DIR *dir_info;
    int dir_count;
    int f_count;
    int idx;
    char dir_name[max_len] = { 0, };
    char f_name[max_len] = {0, };
    if((dir_count = scandir(dir, &dir_list, NULL, alphasort))==-1)
    {
        fprintf(stderr, "error: %s\n", strerror(errno));
        return -1;
    }
    printf("%s\n", "dir_scan_compelete");
    
    // dir_info = opendir(namelist[2]->d_name);   
    // while(filelist =readdir(dir_info)){
    //     remove()
    strcat(dir_name, pt);
    strcat(dir_name, dir_list[2]->d_name);

    if(rmdir(dir_name) == -1)
        {
            printf("dir has files..");
            if((f_count = scandir(dir_name, &f_list, NULL, alphasort))==-1)
            {
                fprintf(stderr, "error: %s\n", strerror(errno));
                return -1;
            }
            printf("%s\n", "file_scan_compelete");

            for (idx=2; idx < f_count; idx++){
                strcpy(f_name, dir_name);
                strcat(f_name, "/");
                strcat(f_name, f_list[idx]->d_name);
                printf("%s\n", f_name);
                if(remove(f_name) == -1)
                {
                    fprintf(stderr, "f_del_error: %s\n", strerror(errno));
                    return -1;
                }
            }
            printf("%s\n", "file_del_compelete");
            if(remove(dir_name) == -1)
                {
                    fprintf(stderr, "error: %s\n", strerror(errno));
                    return -1;
                }
            printf("%s\n", "dir_del_compelete");
            return 0;
                }
            printf("%s\n", "dir_del_compelete");
            return 0;

            
}
void main(){
    rm_olddir(pt);
}