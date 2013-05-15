#include <windows.h>
#include <stdio.h>

char mybuf[59];


int main (int argc, char *argv[])
{
  DWORD text;
  HANDLE errorh =  GetStdHandle(STD_ERROR_HANDLE);
  
  
	/*	int j;
           for (j = 1; j <= 10; j++)
	    {
		  fprintf(stderr, "The Process ID is %d, the numbers are: %i \n",  _getpid(), j);
		  
		  }
   	    sleep(1000);*/
   	    
 Sprintf and write file for final bit */
   memset (mybuf,0,sizeof(mybuf));
  sprintf(mybuf,"Process ID: %d, Numbers: 1,2,3,4,5,6,7,8,9,10 \n",_getpid());
  WriteFile(errorh, mybuf, sizeof(mybuf),&text,NULL);
  

  return 0;
}
