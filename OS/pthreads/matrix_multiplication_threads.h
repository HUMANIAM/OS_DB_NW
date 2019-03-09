/**
in this simple program we compare the execution time of multipling two matrices using only on thread per the 
multiplication process and the execution time of using n*n threads per the multiplication process.
*/

typedef struct{
    int height, width;
    int** matrix;
}Matrix;


typedef struct{
	const Matrix* matrix1;
	const Matrix* matrix2;
	Matrix* result_matrix;
}Params;

/**
Utility functions
*/
Matrix* create_matrix(int, int);
void fill_random(Matrix*, int);
void print_matrix(Matrix*);

//unithread per process
Matrix* unithread_multiplication(const Matrix*, const Matrix*);

//multithreads per process
void* set_cell(void*);

Matrix* multithread_multiplication(const Matrix*, const Matrix*);

bool compare_results(const Matrix*, const Matrix*);