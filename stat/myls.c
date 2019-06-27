#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pwd.h>	// getpwuid()
#include <grp.h>	// getgrgid()
#include <sys/ioctl.h>  // ioctl, TIOCGWINSZ
#include <err.h>        // err
#include <fcntl.h>      // open

#define PERM_LENGTH 	11
#define PATH_LENGTH 	100

#define DEBUG


// setuid bit
// 특징 - 8진수 4000 
// 슈퍼유저(root)만 접근 가능한 파일이나 명령어에 대해 일반유저 접근이 필요시 사용
// setuid 비트가 설정된 파일은 실행 순간만 그 파일의 소유자 권한으로 실행한다.
// 일반 사용자가 사용하는 passwd 명령어도 root가 passwd 명령어 파일에 setuid 저용해서 가능한 것.

// 단점
// ekswja - root 권한이 필요없는 프로그램에 소유주 root, setuid 설정된 경우 보안상 매우 취약
// 만약 cat 명령어에 setuid적용하면, root만 읽을 수 있는 파일도 일반사용자가 cat 명령어로 읽을 수 있다.

// 설정 방법
// chmod 명령어 사용해 8진수(4000)나 기호(u+s)을 이용하여 setuid 비트를 설정할 수 있다.
// setuid bit가 설정되어 있으면 user의 실행권한 자리에 s또는 S로 표시된다.

// setgid bit
// 특징 - 8진수 2000
// setgid bit 설정 시, 이 디렉토리에 새로 생성된 파일들은 디렉토리 그룹 소유권이 아닌 파일 생성자의 그룹 소유권을 얻게 된다.

//방법: chmod 명령어 사용 8진수(2000)나 기호(g+s)를 이용ㅎ
// setuid bit가 설정되어 있으면 group의 실행권한 자리에 s또는 S로 표시됨.

//sticky bit
// 특징 - 8진수 1000
// 리눅스는 파일의 sticky bit 무시
// 특정 디렉토리를 누구나 자유롭게 사용할 수 있게 하기 위해 사용(공용)
// sticky 비트가 디렉토리에 적용되면 디렉토리 소유자나 파일 소유자 또는 관리자가 아닌 사용자들은 파일 사제 or 이름변경하지 못하도록 막음. 파일 또는 디렉토리 생성은 누구나 할 수 있다.
// /tmp 디렉토리에도 sticky bit가 적용되어 있어서 누구나 사용할 수 있는것

// 방법: chmod 명령어8진수(1000)나 기호(o+s) 이용
// setuid bit가 설정되어 있으면 other의 실행권한 자리에 t 또는 T로 표시된다.



//=========================================
// dirent 구조체
//=========================================
/*
struct dirent
{
	long d_ino; //inode 번호
	off_t d_off; // offset
	unsigned short d_reclen; //d_name 길이
	char d_name[NAME_MAX+1]; //파일 이름
};
*/

//=========================================
// stat 구조체
//=========================================
/*
struct stat {
    dev_t     st_dev;     // ID of device containing file 
    ino_t     st_ino;     // inode number 
    mode_t    st_mode;    // 파일의 종류 및 접근권한
    nlink_t   st_nlink;   // hardlink 된 횟수
    uid_t     st_uid;     // 파일의 owner
    gid_t     st_gid;     // group ID of owner
    dev_t     st_rdev;    // device ID (if special file)
    off_t     st_size;    // 파일의 크기(bytes)
    blksize_t st_blksize; // blocksize for file system I/O
    blkcnt_t  st_blocks;  // number of 512B blocks allocated
    time_t    st_atime;   // time of last access
    time_t    st_mtime;   // time of last modification
    time_t    st_ctime;   // time of last status change
};
*/

//=========================================
// group 구조체
//=========================================
/*
struct group {
    char   *gr_name;       // group name 
    char   *gr_passwd;     // group password 
    gid_t   gr_gid;        // group ID 
    char  **gr_mem;        // group members 
};
*/

//=========================================
// group 구조체
//=========================================
/*
struct passwd {
	char *pw_name;
	char *pw_passwd;
	uid_t pw_uid;
	gid_t pw_gid;
	time_t pw_change;
	char *pw_class;
	char *pw_gecos;
	char *pw_dir;
	char *pw_shell;
	time_t pw_expire;
}; 
*/

//=========================================
// Function Name : access Name
// arg1 : permission value
// arg2 : mode 
// return : void
// Description : 
//=========================================
void access_perm(char *perm, mode_t mode)
{
	int i;
	char permchar[] = "rwx";
	memset(perm, '-', 10);
	perm[10] = '\0';

	if (S_ISDIR(mode)) perm[0] = 'd';
	else if (S_ISCHR(mode)) perm[0] = 'c';
	else if (S_ISBLK(mode)) perm[0] = 'b';
	else if (S_ISFIFO(mode)) perm[0] = 'p';
	else if (S_ISLNK(mode)) perm[0] = 'l';

	for (i = 0; i < 9; i++) 
	{
		if ((mode << i) & 0x100)
			perm[i+1] = permchar[i%3];
	}

	if (mode & S_ISUID) perm[3] = 's';
	if (mode & S_ISGID) perm[6] = 's';
	if (mode & S_ISVTX) perm[9] = 't';
}


int main(int argc, char *argv[])
{
	DIR *dp;		// DIR pointer
	struct stat statbuf;	// inode info
	struct dirent *dent;
	struct group *group_entry;
	struct passwd *user_pw;
	struct winsize ws;
	int fd;	

	char perm[PERM_LENGTH];
	char pathname[PATH_LENGTH];
	char dirname[PATH_LENGTH];

	int flag;
	char temp[20];
	
	int col;
	int len;
	//time
	struct tm *tm;
	fd = open("/dev/tty", O_RDWR);
	if (fd < 0)
		err(1, "/dev/tty");
	if (ioctl(fd, TIOCGWINSZ, &ws) < 0)
		err(1, "/dev/tty");
	
	col = ws.ws_col;
	
	if (argc==1)	
		flag = 0;
		strcpy(dirname,".");

	if(argc>1)
	{
		// "-al" 문자열을 비교
		sprintf(temp,"-al");
        	if(!strcmp(temp,argv[1]))
		{
			flag = 1;
			strcpy(dirname,".");
		}
		else
		{
			flag = 2;
			strcpy(dirname, argv[1]);
		}
	}

	if(argc>2)
	{
		flag = 3;
		strcpy(dirname, argv[2]);
	}
		
#ifdef DEBUG	
	printf("dir=%s\n",dirname);
	printf("flag=%d\n",flag);
#endif

	// 디렉토리의 inode정보 읽기
	stat(dirname, &statbuf);

	// 디렉토리가 아닌경우 에러 메시지 출력 후 종료
	if (!S_ISDIR(statbuf.st_mode)) 
	{
		fprintf(stderr, "%s is not directory\n",dirname);
		exit(1);
	}

	// 디렉토리가 정상적으로 열리지 않은 경우
	if ((dp = opendir(dirname)) == NULL) 
	{
		perror("Error:");
		exit(1);
	}
	
#ifdef DEBUG
	// 정상적으로 열리면 디렉토리명을 출력
	printf("Lists of Directory(%s):\n", dirname);
#endif

	// 디렉토리의 내용을 읽어온다. 
	// 더이상 읽을 디렉토리 내용이 없을 때 까지
	while((dent = readdir(dp)) != NULL) 
	{
		sprintf(pathname, "%s/%s", dirname, dent->d_name);
		lstat(pathname, &statbuf);
		access_perm(perm, statbuf.st_mode);
	
		if(flag==1 | flag==3)
		{
			sprintf(pathname, "%s/%s", dirname, dent->d_name);
			lstat(pathname, &statbuf);
			access_perm(perm, statbuf.st_mode);
			user_pw=getpwuid(statbuf.st_uid);
			group_entry=getgrgid(statbuf.st_gid);
			tm = localtime(&statbuf.st_mtime); 
			strftime(temp, sizeof(temp), "%m월 %e %H:%M", tm);
			printf("%s %3ld %6s %6s %8ld %s %s\n", \
				perm, statbuf.st_nlink, user_pw->pw_name, \
				group_entry->gr_name, statbuf.st_size, temp, dent->d_name);
		}
		else		
		{
			if (perm[0] == 'd')
				printf("\x1b[34m");
			else if (perm[0] == '-')
				printf("\x1b[0m");
			else if (perm[0] == 'l')
				printf("\x1b[32m");
			len += (strlen(dent->d_name)+2);
			if (len > col){
				printf("\n");
				len = 0;
			}
		//	printf("%d\n", len);
			printf("%s  ", dent->d_name); 			  			
		}
	}
	printf("\n");
	printf("\x1b[0m");
	closedir(dp);
	return 0;
}
