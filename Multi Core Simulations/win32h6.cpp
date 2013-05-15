#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int N = 0;
int P = 0;
int C = 0;
int X = 0;
int Ptime = 0;
int Ctime = 0; 
int *buffer;

CRITICAL_SECTION cs;
HANDLE queue_empty;
HANDLE queue_full; 
HANDLE Ready;


//pthread_mutex_t queue_lock;
//sem_t queue_empty, queue_full;

 void enqueue(int value)
  {
	int i = 0;
	for(i=0; i<N; i++)
	{
	if(buffer[i]==0){
		buffer[i]=value;
		break;
	}	
	}
	
	fprintf(stderr, "Queue complete \n");
  }
  
  void dequeue()
   {	
    int i;
    int out = buffer[0];
    fprintf(stderr, "Dequeue complete \n");
  	
  	for(i=0;i<X;i++);
 	 {
			buffer[i-1]=buffer[i];
 	 }
 	 buffer[N-1]=0;
   						 						
   }
   
   void spinwait(int times)
   {
	int i;
	for(i=0;  i<times; i++);
		
	}

DWORD WINAPI producerthread(LPVOID thread)
{
DWORD threadID=GetCurrentThreadId();	
int i;


for(i=1; i<=X;i++)
{
EnterCriticalSection(&cs);
enqueue(i);
LeaveCriticalSection(&cs);
SetEvent(Ready);
}

spinwait(Ptime*100000);
return 0; 
}
    
  
DWORD WINAPI consumerthread(LPVOID thread)
{
DWORD threadID=GetCurrentThreadId();	

EnterCriticalSection(&cs);
printf("Spawning Consumer");


dequeue();

LeaveCriticalSection(&cs);
SetEvent(Ready);
spinwait(Ptime*100000);
return 0; 
}




int main(int argc, char *argv[])
{
	int  returnValue;
	int J;
	int H;
	int i;
	HANDLE thread;
	HANDLE threadH;
	HANDLE threadP;
	HANDLE *tids;
	
	

	

	
	
	//Error Check for correct no. of Arguments //
	if (argc != 7)
		{
		printf("7 Arguments required \n", "Program name, N, P, C, X, Ptime, Ctime ");
		exit(0);
		}
	
	// Arguments to Intergers // 
		
	N = atoi(argv[1]);
	P = atoi(argv[2]);
	C = atoi(argv[3]);
	X = atoi(argv[4]);
	Ptime = atoi(argv[5]);
	Ctime = atoi(argv[6]);
    
	buffer = calloc(N,sizeof(int));
	tids = calloc(P+C,sizeof(HANDLE));
    //Semaphore //
    

     queue_empty = CreateSemaphore(NULL,  N, N, NULL);     
     queue_full = CreateSemaphore(NULL,  0, N, NULL);     

	//Time stamp beginning//

	clock_t begin, end, final;
	begin = clock();
	fprintf(stderr,"Startime %d \n",((int)begin));
	
	//Consumer Thread loop
       
		for (J = 0;J<C; J++){
			threadH = CreateThread(NULL, 0, consumerthread,0,0,&thread);
	
				if(threadH == NULL) {
				fprintf(stderr,"Unable to create thread");
				return -1;
									}
			}	
		
		
		//Producer Thread loop
       
		for (H = 0; H <P; H++){
		thread = CreateThread(NULL, 0, producerthread,0,0,&thread);
	
				if(thread == NULL) {
				fprintf(stderr,"Unable to create thread");
				return -1;
									}
		 	}
	
							
							
		for(i=0;i<(P+C);i++)
		{
		pthread_join(tids[i],NULL);	
		}		


	end = clock();
	int total = (end-begin);
	fprintf(stderr, "final time %d \n", ((int)end));
	double finalsec =((double)total/CLOCKS_PER_SEC);
	
	fprintf(stderr, "total execution time %f \n",finalsec);

return 0;
}

