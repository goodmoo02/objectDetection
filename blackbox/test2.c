#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
int main()
{
   DIR            *dir_info;
   struct dirent  *dir_entry;

   dir_info = opendir( ".");              // ?˜„?ž¬ ?””? ‰?† ë¦¬ë?? ?—´ê¸?
   if ( NULL != dir_info)
   {
      while( dir_entry   = readdir( dir_info))  // ?””? ‰?† ë¦? ?•ˆ?— ?žˆ?Š” ëª¨ë“  ?ŒŒ?¼ê³? ?””? ‰?† ë¦? ì¶œë ¥
      {
         printf( "%s\n", dir_entry->d_name);
      }
      closedir( dir_info);
   }   
}
