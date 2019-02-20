# include <stdio.h>
# include <stdlib.h>
#include  <stdbool.h>
#include <pthread.h>
#include "threads_basic.h"

//print messages
void* print_msg(void* msg){
    // some info will be returned to the main thread
    int* someInfo = (int*) malloc(sizeof(int));
    *someInfo = 100;

    // pthread_exit(msg);
    printf("%s\n", (char*)msg);

    //return some info to the main thread
    return msg;
}

// create_some_threads
int create_some_threads(void){
    pthread_t thread1, thread2;
     const char *message1 = "Thread 1";
     const char *message2 = "Thread 2";
     int  iret1, iret2;

    /* Create independent threads each of which will execute function */

     iret1 = pthread_create( &thread1, NULL, print_msg, (void*) message1);
     if(iret1)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
         exit(EXIT_FAILURE);
     }

     iret2 = pthread_create( &thread2, NULL, print_msg, (void*) message2);
     if(iret2)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
         return (EXIT_FAILURE);
     }

     printf("pthread_create() for thread 1 returns: %d\n",iret1);
     printf("pthread_create() for thread 2 returns: %d\n",iret2);

     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */

     char * thread1_return = (char*) malloc(20*sizeof(char));
     char * thread2_return = (char*) malloc(20*sizeof(char));

     pthread_join( thread1, (void**) &thread1_return);
     pthread_join( thread2, (void**) &thread2_return);

     printf("return value form thread 1 is :: %s\n", thread1_return);


     return EXIT_SUCCESS;

}
