# include <stdio.h>
# include <stdlib.h>
#include  <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include "matrix_multiplication_threads.h"

Matrix* create_matrix(int h, int w){
	Matrix* matrix = (Matrix*) malloc(sizeof(Matrix));

	matrix->height = h;
	matrix->width = w;
	matrix->matrix = (int**) malloc(matrix->height * sizeof(int*));

	int i;
	for(i = 0; i<matrix->height; i++)
		matrix->matrix[i] = (int*) malloc(matrix->width * sizeof(int));
	
	return matrix;
}

void fill_random(Matrix* mat, int range){
	int i, j;
	for(i=0; i<mat->height; i++)
		for(j=0; j<mat->width; j++)
			mat->matrix[i][j] = rand() % range;
}

void print_matrix(Matrix* matrix){
	int i, j;
	for(i=0; i<matrix->height; i++){
		for(j=0; j<matrix->width; j++)
			printf("%d  ", matrix->matrix[i][j]);
		printf("\n");
	}
}

//unithread do the multiplication operation of two matrices
Matrix* unithread_multiplication(const Matrix* matrix1, const Matrix* matrix2){
	//create the result matrix
	Matrix* res_matrix = create_matrix(matrix1->height, matrix2->width);

	//multiplication O(n^3)
	int r, c, k;
	for(r = 0; r < matrix1->height; r++){
		for (c = 0; c < matrix2->width; c++){
			res_matrix->matrix[r][c] = 0;
			for(k=0; k < matrix1->width; k++)
				res_matrix->matrix[r][c] += matrix1->matrix[r][k] * matrix2->matrix[k][c];
		}
	} 

	return res_matrix;
}


//multithreads to make the multiplication of two matrices
static volatile int running_threads = 0;
static pthread_mutex_t running_mutex = PTHREAD_MUTEX_INITIALIZER;
static Params* params;

void* set_cell(void* args){
	// compute the corresponding row in the result matrix
	int r = *((int*) args);

	int c, k;
	int height2 = params->matrix2->height;
	int width2 = params->matrix2->width;

	for(c=0; c < width2; c++){
		params->result_matrix->matrix [r][c] = 0;
		for(k=0; k < height2; k++)
			params->result_matrix->matrix[r][c] += params->matrix1->matrix[r][k] 
												   * params->matrix2->matrix[k][c];
    }

	//decrease the running thread
	pthread_mutex_lock(&running_mutex);
    running_threads--;
    pthread_mutex_unlock(&running_mutex);

    //return
	return NULL;
}

Matrix* multithread_multiplication(const Matrix* matrix1, const Matrix* matrix2){
	//create the result matrix
	int h = matrix1->height;
	int w = matrix2->width;
	params = (Params*) malloc(sizeof(Params));
	params->matrix1 = matrix1;
	params->matrix2 = matrix2;
	params->result_matrix = create_matrix(h, w);

	//running threads
	int threads_n = running_threads = h;
	int rows [threads_n]; 


	//start multiplication using threads
	pthread_t threads[threads_n];
	int r;
	for(r = 0; r < h; r++){
		rows[r] = r;
		pthread_create(&threads[r], NULL, set_cell, (void*) &rows[r]);
	} 

	//wait all threads untill complete
	while (running_threads > 0)	sleep(1);
  

  //return the result matrix
  return params->result_matrix;
}


//compare results of unithread and multithread
bool compare_results(const Matrix* matrix1, const Matrix* matrix2){
	int i, j;
	for(i=0; i < matrix1->height; i++)
		for(j=0; j < matrix2->width; j++)
			if(matrix1->matrix [i][j] != matrix2->matrix [i][j])
				return false;
	return true;
}
