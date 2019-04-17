#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define READERS 5
#define WRITERS 5
#define NUM_READ 5
#define NUM_WRITE 5

//conditions variables
pthread_cond_t c_read = PTHREAD_COND_INITIALIZER; /* readers waits on this cond var */
pthread_cond_t c_write = PTHREAD_COND_INITIALIZER; /* writer waits on this cond var */

//mutexes
pthread_mutex_t cs_m = PTHREAD_MUTEX_INITIALIZER;  		/* mutex lock for critical section */

//global shared sections
int cs;							//critical section among threads
int activeReaders, waitReaders;	// 0 > no reader and no writer, -1 > 1 writer 0 reader, 1 > 1 reader and 0 writer

//procedure of read thread
void* read_cs(void* args){
	int id = *((int*) args);
	int i, numReaders;
	for(i = 0; i < NUM_READ; i++){
		sleep(rand()%2);
		//acquire the cs mutex to start reading
		pthread_mutex_lock(&cs_m);
		waitReaders++;
		//wait if there is a writer
		while(activeReaders == -1)
			pthread_cond_wait(&c_read, &cs_m);

		waitReaders--;
		numReaders =  ++activeReaders;
		pthread_mutex_unlock(&cs_m);

		//read current value of critical section
		printf("Thread : %d read : %d readers : %d\n", id, cs, numReaders);

		//signal waitting writers
		pthread_mutex_lock(&cs_m);
		activeReaders--;

		//if there are no active readers signal the writer
		if(activeReaders == 0)
			pthread_cond_signal(&c_write);
		pthread_mutex_unlock(&cs_m);
	}

	pthread_exit(0);
} 

//procedure of write thread
void* write_cs(void* args){
	int id = *((int*) args);
	int i, numReaders = 0;

	for(i = 0; i < NUM_READ; i++){
		sleep(rand()%2);
		//acquire the cs mutex to start writting
		pthread_mutex_lock(&cs_m);

		//wait if there is a writer
		while(activeReaders != 0)
			pthread_cond_wait(&c_write, &cs_m);

		activeReaders = -1;
		pthread_mutex_unlock(&cs_m);

		//increment cs
		printf("Thread : %d write : %d readers : %d \n", id, ++cs, numReaders);


		//signal r/w threads that current thread done
		pthread_mutex_lock(&cs_m);
		activeReaders = 0;

		//broadcast waiting read threads
		if(waitReaders > 0)
			pthread_cond_broadcast(&c_read);
		else
			//signal write threads
			pthread_cond_signal(&c_write);
		
		pthread_mutex_unlock(&cs_m);
	}

	pthread_exit(0);
}

// wait all threads till done
void wait_all_threads(pthread_t* readers, pthread_t* writers){
	int i;
	//wait readers
	for(i = 0; i < READERS; i++)
		pthread_join(readers[i], NULL);
	//wait writers
	for (i = 0; i < WRITERS; ++i)
		pthread_join(writers[i], NULL);
}

//main
int main(int argc, char const *argv[]){
	//seeding psudo random generator
	srand((unsigned int)time(NULL));
	int i;
	pthread_t writers[WRITERS], readers[READERS];
	int writers_ids[WRITERS], readers_ids[READERS];

	//launch writers threads
	for(i = 0; i < WRITERS; i++){
		writers_ids[i] = i;
		if(pthread_create(&writers[i], NULL, write_cs, (void*) &writers_ids[i]) != 0) {
			fprintf(stderr, "Unable to create writer thread\n");
			exit(1);
		}
	}

	//launch readers threads
	for(i = 0; i < READERS; i++){
		readers_ids[i] = i;
		if(pthread_create(&readers[i], NULL, read_cs, (void*) &readers_ids[i]) != 0) {
			fprintf(stderr, "Unable to create writer thread\n");
			exit(1);
		}
	}

	//wait all of them till finish their jobs
	wait_all_threads(readers, writers);

	return 0;
}