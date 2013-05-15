#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>
#include <math.h>

int N = 0;
int P = 0;
int C = 0;
int X = 0;
int Ptime = 0;
int Ctime = 0; 

int *buffer;
pthread_mutex_t queue_lock;
sem_t queue_empty, queue_full;

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
  
    int out = buffer[0],i;
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

  void producerthread(void *thread)
  {
	int i;
	for(i=1; i<=X;i++)
	{
	fprintf(stderr,"Producer thread i=%d \n", i);
	sem_wait(&queue_empty);
	pthread_mutex_lock(&queue_lock);	
	
	enqueue(i);
	
	
	pthread_mutex_unlock(&queue_lock);	
	sem_post(&queue_full);	
	spinwait(Ptime*100000);
	 }
    
  
   
   
  }
  
 void consumerthread(void *thread)
{
	printf("spawning consumer \n");
	int i;
	for (i=1; i<(P*X/C); i++)
	{
	sem_wait(&queue_full);
	pthread_mutex_lock(&queue_lock);
	
	dequeue();
	
	pthread_mutex_unlock(&queue_lock);
	sem_post(&queue_empty);
	spinwait(Ctime*100000);
	
    }
}



int main(int argc, char *argv[])
{
	int  returnValue, J, H, i;
	void *arg;
	pthread_t thread;
	pthread_t *tids;
	
	buffer = calloc(N,sizeof(int));
	tids = calloc((P+C),sizeof(pthread_t));
	
	if((pthread_mutex_init(&queue_lock,NULL))<0)
	{
		perror("Can't initialize mutex \n");
		exit(-1);
	}
	
	
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
    
    //Semaphore 
	sem_init(&queue_empty, 0, N);
	sem_init(&queue_full,0,0);
	
	//Time stamp beginning//
	clock_t begin, end, final;
	begin = clock();
	fprintf(stderr,"Startime %d \n",((int)begin));
	
	
	//Consumer Thread loop
       
		for (J = 0;J<C; J++){
			if((pthread_create(&tids[J], NULL,(void*)consumerthread,arg))<0){
			
			perror("Thread Creation Unsuccessful\n");
			
			exit(-1);
 
			}
		}	
		
		//Producer Thread loop
       
		for (H = 0;H <P; H++){
			if((pthread_create(&tids[C+H], NULL,(void*)producerthread,arg))<0)
			{	
			perror("Thread Creation Unsuccessful \n");
			exit(-1);
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


}


