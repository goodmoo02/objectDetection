#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //access
#include <libgen.h>
#include <errno.h>
#include <sys/vfs.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>



// #define DEBUG
//	#include "debug_message.h"
// #ifdef DEBUG    // DEBUG�� ���ǵǾ� �ִٸ� debug_message.h ��� ���� ����
// #include "message.h"
// #else           // �ƴϸ� message.h ��� ���� ����
// #endif

#define size 256
#define event_dir "./event"
#define always_dir "./always"

// ���� ����? �� ���� �� �� ��?.
int indent = 0;
int dir_size = 0;
struct f_size
{
	long blocks;
	long avail;
	long avail_per;
};

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


 

void subdirOutput(char *wd)
{
    struct dirent *dentry;
    struct stat fstat;
    DIR *dirp;
    int i;

    // ��? ���� ����? ����.
    if(chdir(wd) < 0) {
        printf("error: chdir..\n");
		// fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }

    // ��? �� ����? ��.
    if((dirp = opendir(".")) == NULL) {
        printf("error: opendir..\n");
        exit(1);
    }

    // �� ����? �� ��? ��?.
    while(dentry = readdir(dirp)) {
        // ����? ��? ������? 0 �� �� ��?.
        // ������? 0 �� ? �� ��? ? ��?.
        if(dentry->d_ino != 0) {
            // ��? ��? "."(������)? ".."(������)? ����.
            // �� �� ����? ���� ��? ��? ���� ��?.
            if((!strcmp(dentry->d_name, ".")) || (!strcmp(dentry->d_name, "..")))
                continue;

            // �� ��? ����? ����.
            stat(dentry->d_name, &fstat);

            // �� ����? ��? �� �� �� ��?
            // ���� �� ���� Tab�� ����.
            for(i = 0; i < indent; i++)
                printf("\t");
   
            // �� ��? ��? ����? �� 
            // ���� ���� ���� �� ��? ���� ?
            // subdirOutput��? �� ����? �� ���� ��? ����.
            if(S_ISDIR(fstat.st_mode)) {
                // printf("%s\n", dentry->d_name);
                indent++;
                subdirOutput(dentry->d_name);

            // �� ��? ��? ����? �� ��
            // ������ �� �� ���� ��
            // Tab�� ���� ��? ����.
            } 
			else {
                printf("\r");
				// dir_size += fstat.st_size;
                dir_size += fstat.st_blksize * fstat.st_blocks;
            }
			
        }
    }
    // �� �� ����? ��? ����? ����.
    // ��? ���� ����? �� ���� ��? ����? 
    // ���� �� ��? �� ��? �� ����? ����.
    closedir(dirp);
    indent--;
    chdir("..");
}








struct f_size* avail(char* dirname)
{
	char buf[256];
	char null[16];
	float avail;
	int trans;
	struct statfs lstatfs;
	struct stat lstat;
	struct f_size* lf_size;

	lf_size = (struct f_size*)malloc(sizeof(lf_size));

	if (stat(dirname, &lstat) == -1)
	{
		perror("stat_error");
		return NULL;
	}
	printf("%d\n", S_ISBLK(lstat.st_mode));  
	if (statfs(dirname, &lstatfs) == -1) {
		perror("statfs_error");
		return NULL;
	}
	lf_size->blocks = lstatfs.f_blocks * (lstatfs.f_bsize / 1024);
	// ���� �ý��� �� �� ������ ���� * ����ȭ�� ���� ���� ũ�� / 1024
	lf_size->avail = lstatfs.f_bavail * (lstatfs.f_bsize / 1024);
	// ��-���� ������ ���� ���� ���� * ����ȭ�� ���� ���� ũ�� / 1024
	lf_size->avail_per = lstatfs.f_bavail / lstatfs.f_blocks;
	return lf_size;
}


int main(int argc, char* argv[])
{
	struct f_size* f_inf;
	mkalwaysdir();
	if ((f_inf = avail(argv[1])) == NULL)
	{
		perror("avail error");
		return 1;
	}

	printf("�� ������: %ld\n���� ������: %ld\n���� ����: %ld\n", f_inf->blocks, f_inf->avail, f_inf->avail_per);
	free(f_inf);
}


// subdirOuput �Լ� test��
//int main()
//{
//    printf("Sub-Directory Ouput!!!\n");
//    printf("----------------------\n");
//	
// 
//
//    // �� ����? �� ����? ����?.
//    subdirOutput("/home/jiwoong/objectDetection/pthread");
//    printf("size: %d\n", dir_size);
// 
//    return 0;
//}

// void main(){
	// int num1 = mkeventdir();
	// int num2 = mkalwaysdir();
	// printf("%d\n", num1);
	// printf("%d\n", num2);

// }


