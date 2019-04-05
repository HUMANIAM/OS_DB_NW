/* PThread Creation */ 

#include <stdio.h>
#include <pthread.h>

void *foo (void *arg) {		/* thread main */
	printf("Foobar!\n");
	pthread_exit(NULL);
}

int main (void) {

	int i;
	pthread_t tid[10];
	pthread_attr_t attr[10];

	for (int i = 0; i < 10; ++i){
		pthread_attr_init(&attr[i]); // Required!!!
		pthread_attr_setdetachstate(&attr[i], PTHREAD_CREATE_DETACHED);
		pthread_attr_setscope(&attr[i], PTHREAD_SCOPE_SYSTEM);
		pthread_create(&tid[i], &attr[i], foo, NULL);
	}
	
	
	// pthread_join(tid, NULL);

	return 0;
}


