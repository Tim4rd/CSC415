#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int count;
CRITICAL_SECTION cs;
HANDLE Ready; 

DWORD WINAPI threado(LPVOID Param)
{
int tcounter=0;
DWORD threadID=GetCurrentThreadId();	

EnterCriticalSection(&cs);
fprintf(stderr, "Hello I'm Thread Number: %u \n", threadID);
tcounter = count;

fprintf(stderr, "Hello I'm Thread Number %u, Thread Counter: %d\n", threadID, tcounter);
tcounter = tcounter+10;
fprintf(stderr,"Hello I'm Thread Number %u, Thread Counter 2:  %d\n", threadID, tcounter);
count = tcounter;
sleep(1);

//Remove below to create deadlock// 
LeaveCriticalSection(&cs);
SetEvent(Ready);
return 0; 
}

int main()
{

int i;
DWORD thread;
HANDLE threadH;

InitializeCriticalSection (&cs);


	//Time stamp beginning//
	clock_t begin, end, final;
	begin = clock();
	fprintf(stderr,"Startime %d \n",((int)begin));

for (i = 0; i<10; i++)
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
DeleteCriticalSection(&cs);
fprintf(stderr,"Main routine finished\n");

//end clock
	end = clock();
	int total = (end-begin);
	fprintf(stderr, "final time %d \n", ((int)end));
	double finalsec =((double)total/CLOCKS_PER_SEC);
	
	fprintf(stderr, "total execution time %f \n",finalsec);
    

}

