#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int count;
 
DWORD WINAPI threado(LPVOID Param)
{
int tcounter=0;
DWORD threadID=GetCurrentThreadId();	


fprintf(stderr, "Hello I'm Thread Number: %u \n", threadID);
tcounter = count;

fprintf(stderr, "Hello I'm Thread Number %u, Thread Counter %d\n", threadID, tcounter);
tcounter = tcounter+10;

fprintf(stderr,"Hello I'm Thread Number %u, Thread Counter 2 %d\n", threadID, tcounter);
count = tcounter;
return 0; 

}

int main()
{

int i;
DWORD thread;
HANDLE threadH;

for (i = 0; i<=10; i++)
{
	threadH = CreateThread(NULL, 0, threado,0,0,&thread);
	
	if(threadH == NULL) {
		fprintf(stderr,"Unable to create thread");
		return -1;
	}
}

WaitForSingleObject(threadH, INFINITE);
CloseHandle(threadH);

fprintf(stderr, "\nCount:%d", count);

}

