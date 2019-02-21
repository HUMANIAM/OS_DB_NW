/**
Author :    Ibrahim Saad
Date :      20/2/2019
Program :   posix threads

*/

/**
* This program is about training on the posix threads and multithreading in c to understand processes, threads, synchoronization, sheduling, data management, interprocess communication
* pthread is standard based thread api for c/c++ allows one to spwan a new concrent processes flow. and it effective in multiprocessor or multicore systems
* the process flow can be sheduled to run on anthor processor so gaining speed through parallel or distributed processing
* threads require less overhead than "forking" a new process because the system does not initialize a new system virtual memory space and environment for the process
* One thread may execute while another is waiting for I/O or some other system latency
* parallel programming techs such as MPI and PVM are used in a distributed computing systems but threads are limited to a single computer system
* All threads within the process share address space.
* a thread is spawned by defining a function that the thread will execute it and its arguments which will be processed in the thread.
* the cost of creating and maintaining threads is much smaller than the cost for processes, both in system resources and time. 
* communication between threads can be made without involving the operating system
*
*
*
* The purpose of using the Posix thread library in any software is to make it faster
*/

# include <stdio.h>
# include <stdlib.h>
#include  <stdbool.h>
#include <pthread.h>
#include "threads_basic.h"
#include "matrix_multiplication_threads.h"


//main function
int main(){

	//seed pseduorandom generator with current time
	srand(time(NULL));
	//create two matrices say one with dim 6x5 and the second with 5x10
	Matrix* matrix1 = create_matrix(3, 2);
	Matrix* matrix2 = create_matrix(2, 3);

	

	//assign rondom values for matrix 1 and 2
	fill_random(matrix1, 2);
	fill_random(matrix2, 2);
	

	//print the matrix
	printf("* the first matrix:\n");
	print_matrix(matrix1);
	printf("* the second matrix:\n");
	print_matrix(matrix2);

	clock_t start_time, end_time;
	//multiply them by just one thread
	start_time = clock();
	Matrix* result_matrix1 = unithread_multiplication(matrix1, matrix2);
	end_time = clock();

	//print the result matrix of unithread
	printf("the reuslut matrix of unithread_multiplication: \n");
	print_matrix(result_matrix1);
	
	//print time taken with one thread
	printf("unithread_multiplication : %ld ticks\n", end_time - start_time);	

	//multipling using multithreading
	start_time = clock();
	Matrix* result_matrix2 = multithread_multiplication(matrix1, matrix2);
	end_time = clock();

	//print the result matrix of multithread
	printf("\n\nthe reuslut matrix of multithread_multiplication: \n");
	print_matrix(result_matrix2);
	
	//print time taken with one thread
	printf("multithread_multiplication : %ld ticks\n", end_time - start_time);	

	//compare results
	bool cmp = compare_results(result_matrix1, result_matrix2);
	if(cmp)
		printf("They are the same\n");
	else
		printf("They are different\n");
   return 0;
}
