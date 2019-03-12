/*
assume there are many threads some of them are readers and some of them are writers and they all have access
to a critical section say queue. and we sync between them where there are no overwritting or overlapping
among them and also every thread read a consistent data. we mutex besides condition variables to sync among
threads.

scenarios
--------
1- write thread can write only when there are no write threads and read threads
2- read thread can only read when there are no write thread
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define THREAD_NUM 20

pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t finished_signal = PTHREAD_COND_INITIALIZER;
pthread_cond_t read_signal = PTHREAD_COND_INITIALIZER;
pthread_cond_t write_signal = PTHREAD_COND_INITIALIZER;

int list_status = 0;		//no reader and no writer
int finishedThreads;
int threadone;

int write_threads[THREAD_NUM / 2];

// int write_threads_ids
void init_wthreadsIds(){
	size_t i = 0;
	while(i < THREAD_NUM/2) write_threads[i++] = -1;
}

// print current state of the list
void print_list(){
	printf("Current state of the list : \n");
	size_t i = 0;
	while(i < THREAD_NUM / 2) printf("%d ", write_threads[i++]); 
	printf("\n");
}

//read routine
void* print_exe_write_threads(void* args){
	// acquire the mutex to start reading
	pthread_mutex_lock(&counter_mutex);

	//wait if there is a thread writting in execution
	while(list_status == -1)
		pthread_cond_wait(&read_signal, &counter_mutex);

	list_status++;
	pthread_mutex_unlock(&counter_mutex);

	//read the current state of 
	print_list();

	//signal the parent that current thread is done
	pthread_mutex_lock(&counter_mutex);
    threadone = 1;
    finishedThreads++;
    pthread_cond_signal(&finished_signal);
    pthread_mutex_unlock(&counter_mutex);

    //signal waitting writting threads
    pthread_mutex_lock(&counter_mutex);
	list_status--;

	pthread_cond_signal(&write_signal);
	
	pthread_mutex_unlock(&counter_mutex);
	return EXIT_SUCCESS;
}

//write routine
void* update_write_thread_list(void* args){
	size_t id = *((int*) args);
	//acquire the mutex to start writting
	pthread_mutex_lock(&counter_mutex);
	while(list_status != 0)
		pthread_cond_wait(&write_signal, &counter_mutex);

	list_status = -1;
	pthread_mutex_unlock(&counter_mutex);

	// writting operation
	write_threads[id] = id;

	//tell the parent that this thread is done
	pthread_mutex_lock(&counter_mutex);
    threadone = 1;
    finishedThreads++;
    printf("%d write thread is done\n", (int)id);
    pthread_cond_signal(&finished_signal);
    pthread_mutex_unlock(&counter_mutex);

    //signal r/w threads that current thread done
	pthread_mutex_lock(&counter_mutex);
	list_status = 0;

	//signal read threads
	pthread_cond_broadcast(&read_signal);

	//signal write threads
	pthread_cond_signal(&write_signal);
	
	pthread_mutex_unlock(&counter_mutex);

	return EXIT_SUCCESS;
}

//wait all threads untill done
void wait_threads(){
	while(finishedThreads != THREAD_NUM){
		threadone = 0;
		while (threadone == 0)
		           pthread_cond_wait(&finished_signal, &counter_mutex);
		pthread_mutex_unlock(&counter_mutex);
	}
}


//main
int main(int argc, char const *argv[]){
	//init write threads ids
	init_wthreadsIds();
	size_t write_indexes[THREAD_NUM / 2];
	size_t p = 0;
	pthread_t pthreads[THREAD_NUM];

	//launch write threads
	while(p < THREAD_NUM / 2){
		write_indexes[p] = p;
		pthread_create(&pthreads[p], NULL, update_write_thread_list, (void*) &write_indexes[p++]);
	}

	//launch read threads
	while(p < THREAD_NUM){
		pthread_create(&pthreads[p++], NULL, print_exe_write_threads, NULL);
	}

	//wait all threads till be done
	wait_threads();
	//print array
	
	return 0;
}