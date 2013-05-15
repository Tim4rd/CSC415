//Timothy Ford - SFSU //
// CSC 415 - Professor Murphy//


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
//#include <string.h>
#include <semaphore.h>



int count;
pthread_t tid[2];
pthread_mutex_t lock;
sem_t s_signal;

/*Thread*/
void threadfunc(void *thread){
	sem_wait(&s_signal);
	pthread_mutex_lock(&lock);
	
	int tcounter = 0;
	unsigned int threadNo = (unsigned int)pthread_self();
	
	fprintf(stderr, "This is thread number %u \n", threadNo, tcounter);
	tcounter=count;
    //sleep(1); 
	fprintf(stderr, "Thread number %u, total counter %d \n", threadNo, tcounter);
	tcounter = tcounter+10;
	fprintf(stderr, "The number %u, Total Counter 2: %d \n", threadNo, tcounter);
	count=tcounter;
	
//	pthread_mutex_unlock(&lock);
//	sem_post(&s_signal);
	
}

	
int main (int argc, char *argv[])
{
       if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
		int returnV, J;
		void *arg;
		
		pthread_t thread;
		for (J = 1; J<10; J++){
			if((returnV=pthread_create(&thread, NULL,(void*)threadfunc,arg))<0){
			
			perror("Thread Creation Unsuccessful");
			
			exit(-1);
		}
		
		
		
	}
	
	sem_post(&s_signal);
	pthread_join(thread,NULL);
	fprintf(stderr,"\n count: %d \n", count);
	return 0;
    //pthread_mutex_destroy(&lock);
	sem_init(&s_signal,0,0);
}
