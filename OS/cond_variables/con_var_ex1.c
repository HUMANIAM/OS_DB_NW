#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define THREAD_NUM 20

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t myConVar = PTHREAD_COND_INITIALIZER;
int finishedThreads;
pthread_t threadid;

void * exec_routine(void* tid) {
    sleep(rand() % 2);

    pthread_mutex_lock(&my_mutex);

    threadid = pthread_self();
    printf("I am done : %d\n", *((int*) tid));
	finishedThreads++;
    pthread_cond_signal(&myConVar);

    pthread_mutex_unlock(&my_mutex);
}

// wait all threads till they finished
void wait_threads(){
	while(finishedThreads != THREAD_NUM){
		threadid = 0;
		while (threadid == 0)
		           pthread_cond_wait(&myConVar, &my_mutex);
		//printf("Finished Thread : %ld\n", threadid);
		//printf("Number of finished Threads : %d\n", finishedThreads);
		pthread_mutex_unlock(&my_mutex);
	}
}

//main function
int main(int argc, char** argv) {
	int p = 0;
    srand(time(0));
    pthread_t pthreads[THREAD_NUM];
    size_t tids [THREAD_NUM];

    //launch threads
    while(p < THREAD_NUM){
    	tids[p] = (size_t) p;
    	pthread_create(&pthreads[p++], NULL, exec_routine, (void*) &tids[p]);
    }

	//wait all thread till finished
	wait_threads();
    return (EXIT_SUCCESS);
}
