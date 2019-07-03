#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> //access
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
	
// #define DEBUG
//	#include "debug_message.h"
// #ifdef DEBUG    // DEBUG°¡ Á¤ÀÇµÇ¾î ÀÖ´Ù¸é debug_message.h Çì´õ ÆÄÀÏ Æ÷ÇÔ
// #include "message.h"
// #else           // ¾Æ´Ï¸é message.h Çì´õ ÆÄÀÏ Æ÷ÇÔ
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

// access ÇÔ¼ö - µð·ºÅä¸® À¯¹« ¹× ±ÇÇÑ È®ÀÎ
// R_OK : ÆÄÀÏ Á¸Àç ¿©ºÎ, ÀÐ±â ±ÇÇÑ ¿©ºÎ
// W_OK : ÆÄÀÏ Á¸Àç ¿©ºÎ, ¾²±â ±ÇÇÑ ¿©ºÎ
// X_OK : ÆÄÀÏ Á¸Àç ¿©ºÎ, ½ÇÇà ±ÇÇÑ ¿©ºÎ
// F_OK : ÆÄÀÏ Á¸Àç ¿©ºÎ 

// 00 - ÆÄÀÏ ¹× µð·ºÅä¸®°¡ Á¸Àç ÇÏ´ÂÁö Á¶»ç
// 02 - ¾²±â Á¢±ÙÀÌ Çã¿ëµÇ´ÂÁö Á¶»ç
// 04 - ÀÐ±â Á¢±ÙÀÌ Çã¿ëµÇ´ÂÁö Á¶»ç
// 06 - ÀÐ±â ¹× ¾²±â°¡ Çã¿ëµÇ´ÂÁö Á¶»ç

//	char *pathname = "./hello.txt";
// 	int mode = R_OK | W_OK;
// 	if( access( pathname, mode ) == 0 )
// 		printf("ÀÐ°í ¾µ ¼ö ÀÖ½À´Ï´Ù.");
// 	else
// 		printf("±ÇÇÑÀÌ ¾ø°Å³ª Á¸ÀçÇÏÁö ¾Ê½À´Ï´Ù.");


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


int mk

 

// ¿¿¿ ¿¿ ¿¿ ¿¿¿¿¿ ¿¿ ¿¿¿¿¿ ¿¿¿¿ ¿¿.
void subdirOutput(char *wd);

 

// ¿¿¿¿ ¿¿¿¿¿ ¿¿ ¿¿¿¿ ¿¿ ¿¿ ¿¿¿.
int indent = 0;
 

int main()
{
    printf("Sub-Directory Ouput!!!\n");
    printf("----------------------\n");

 

    // ¿¿ ¿¿¿¿¿ ¿¿ ¿¿¿¿¿ ¿¿¿¿¿.
    subdirOutput(".");

 

    return 0;
}

 

void subdirOutput(char *wd)
{
    struct dirent *dentry;
    struct stat fstat;
    DIR *dirp;
    int i;

 

    // ¿¿¿ ¿¿¿¿ ¿¿¿¿¿ ¿¿¿¿.
    if(chdir(wd) < 0) {
        printf("error: chdir..\n");
        exit(1);
    }

 

    // ¿¿¿ ¿¿ ¿¿¿¿¿ ¿¿.
    if((dirp = opendir(".")) == NULL) {
        printf("error: opendir..\n");
        exit(1);
    }

 

    // ¿¿ ¿¿¿¿¿ ¿¿ ¿¿¿ ¿¿¿.
    while(dentry = readdir(dirp)) {

 

        // ¿¿¿¿¿ ¿¿¿ ¿¿¿¿¿¿¿ 0 ¿¿ ¿¿ ¿¿¿.
         // ¿¿¿¿¿¿¿ 0 ¿¿ ¿ ¿¿ ¿¿¿ ¿ ¿¿¿.
         if(dentry->d_ino != 0) {

 

            // ¿¿¿ ¿¿¿ "."(¿¿¿¿¿¿)¿ ".."(¿¿¿¿¿¿)¿ ¿¿¿¿.
            // ¿¿ ¿¿ ¿¿¿¿¿ ¿¿¿¿ ¿¿¿ ¿¿¿ ¿¿¿¿ ¿¿¿.
            if((!strcmp(dentry->d_name, ".")) || (!strcmp(dentry->d_name, "..")))
                continue;

 

            // ¿¿ ¿¿¿ ¿¿¿¿¿ ¿¿¿¿.
            stat(dentry->d_name, &fstat);

 

            // ¿¿ ¿¿¿¿¿ ¿¿¿ ¿¿ ¿¿ ¿¿ ¿¿¿
            // ¿¿¿¿ ¿¿ ¿¿¿¿ Tab¿¿ ¿¿¿¿.
            for(i = 0; i < indent; i++)
                printf("\t");
   
            // ¿¿ ¿¿¿ ¿¿¿ ¿¿¿¿¿ ¿¿ 
            // ¿¿¿¿ ¿¿¿¿ ¿¿¿¿ ¿¿ ¿¿¿ ¿¿¿¿ ¿
            // subdirOutput¿¿¿ ¿¿ ¿¿¿¿¿ ¿¿ ¿¿¿¿ ¿¿¿ ¿¿¿¿.
            if(S_ISDIR(fstat.st_mode)) {
                printf("%s\n", dentry->d_name);
                indent++;
                subdirOutput(dentry->d_name);
   
            // ¿¿ ¿¿¿ ¿¿¿ ¿¿¿¿¿ ¿¿ ¿¿
            // ¿¿¿¿¿¿ ¿¿ ¿¿ ¿¿¿¿ ¿¿
            // Tab¿¿ ¿¿¿¿ ¿¿¿ ¿¿¿¿.
            } else {
                printf("\r");
            }
        }
    }

 

    // ¿¿ ¿¿ ¿¿¿¿¿ ¿¿¿ ¿¿¿¿¿ ¿¿¿¿.
    // ¿¿¿ ¿¿¿¿ ¿¿¿¿¿ ¿¿ ¿¿¿¿ ¿¿¿ ¿¿¿¿¿ 
    // ¿¿¿¿ ¿¿ ¿¿¿ ¿¿ ¿¿¿ ¿¿ ¿¿¿¿¿ ¿¿¿¿.
    closedir(dirp);
    indent--;
    chdir("..");
}


void main(){
	int num1 = mkeventdir();
	int num2 = mkalwaysdir();
	printf("%d\n", num1);
	printf("%d\n", num2);
}



	
