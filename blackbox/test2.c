#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
int main()
{
   DIR            *dir_info;
   struct dirent  *dir_entry;

   dir_info = opendir( ".");              // ??¬ ?? ? λ¦¬λ?? ?΄κΈ?
   if ( NULL != dir_info)
   {
      while( dir_entry   = readdir( dir_info))  // ?? ? λ¦? ?? ?? λͺ¨λ  ??Όκ³? ?? ? λ¦? μΆλ ₯
      {
         printf( "%s\n", dir_entry->d_name);
      }
      closedir( dir_info);
   }   
}
