#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include <sys/vfs.h>
#include <sys/stat.h>
#include <sys/types.h>

const char *MMOUNT = "/proc/mounts";

struct f_size
{
    long blocks;
    long avail; 
};

typedef struct _mountinfo 
{
    FILE *fp;                // 파일 스트림 포인터    
    char devname[80];        // 장치 이름
    char mountdir[80];        // 마운트 디렉토리 이름
    char fstype[12];        // 파일 시스템 타입
    struct f_size size;        // 파일 시스템의 총크기/사용율 
} MOUNTP;

MOUNTP *dfopen()
{
    MOUNTP *MP;

    // /proc/mounts 파일을 연다.
    MP = (MOUNTP *)malloc(sizeof(MOUNTP));
    if(!(MP->fp = fopen(MMOUNT, "r")))
    {
        return NULL;
    }
    else
        return MP;
}

MOUNTP *dfget(MOUNTP *MP)
{
    char buf[256];
    char *bname;
    char null[16];
    struct statfs lstatfs;
    struct stat lstat; 
    int is_root = 0;

    // /proc/mounts로 부터 마운트된 파티션의 정보를 얻어온다.
    while(fgets(buf, 255, MP->fp))
    {
        is_root = 0;
        sscanf(buf, "%s%s%s",MP->devname, MP->mountdir, MP->fstype);
         if (strcmp(MP->mountdir,"/") == 0) is_root=1;
        if (stat(MP->devname, &lstat) == 0 || is_root)
        {
            if (strstr(buf, MP->mountdir) && S_ISBLK(lstat.st_mode) || is_root)
            {
                // 파일시스템의 총 할당된 크기와 사용량을 구한다.        
                statfs(MP->mountdir, &lstatfs);
                MP->size.blocks = lstatfs.f_blocks * (lstatfs.f_bsize/1024); 
	// 파일 시스템 내 총 데이터 블럭 * 최적화된 전송 블럭 크기 / 1024
                MP->size.avail  = lstatfs.f_bavail * (lstatfs.f_bsize/1024); 
                return MP;
	// 비-슈퍼 유저를 위한 여유 블럭 * 최적화된 전송 블럭 크기 / 1024
            }
        }
    }
    rewind(MP->fp);
    return NULL;
}

int dfclose(MOUNTP *MP)
{
    fclose(MP->fp);
}

int main()
{   
    int availe_size;
    MOUNTP *MP;
    if ((MP=dfopen()) == NULL)
    {
        perror("error");
        return 1;
    }
    printf("%s", "File    1K-Blocks    used    Avatilable    Use    Mount-on ");
    while(1)
    {
        while(dfget(MP))
        {
	    printf("%8s%10s%13lu%12lu", MP->mountdir, MP->devname, MP->size.blocks, MP->size.avail);
        }
        printf("=========================\n\n");
        sleep(1);
    }
}
