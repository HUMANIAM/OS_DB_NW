#include <bits/stdc++.h> 
using namespace std; 
// maximum size of matrix
#define MAX 20

// maximum number of threads
#define MAX_THREAD 20

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX];


// multithread multiplicatin
void* multithread_multiplication(void* arg){
    int r = *((int*) arg);

    // Each thread computes 1/4th of matrix multiplication
    for (int c = 0; c < MAX; c++)
        for (int k = 0; k < MAX; k++)
            matC[r][c] += matA[r][k] * matB[k][c];
}

// unithread multiplication
void unithread_multiplicatin(){
    //compute
    for (int i = 0; i < MAX; i++) 
        for (int j = 0; j < MAX; j++)
            for(int k=0; k < MAX; k++)
                matC[i][j] += matA[i][k] * matB[k][j];
}

// print matrix
void print_mat(int mat [][MAX] ){
     for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

//initialize a matrix randomly
void random_init_matrix(){
    // Generating random values in matA and matB
    for (int i = 0; i < MAX; i++) 
        for (int j = 0; j < MAX; j++) {
            matA[i][j] = rand() % 10;
            matB[i][j] = rand() % 10;
        }
}


//main
int main(){
	//init the two matrices randomly
    random_init_matrix();

    // Displaying matA
    cout << "\nMatrix A" << endl;
    print_mat(matA);

    // Displaying matB
    cout << "Matrix B" << endl;
    print_mat(matB);

    // IDs for threads
    pthread_t threads[MAX_THREAD];
    int rows [MAX];

    time_t start_time = time(NULL);
    // Creating four threads, each evaluating its own part
    for (int i = 0; i < MAX_THREAD; i++) {
        rows[i] = i;
        pthread_create(&threads[i], NULL, multithread_multiplication, (void*)&rows[i]);
    }

    // joining and waiting for all threads to complete
    for (int i = 0; i < MAX_THREAD; i++)
        pthread_join(threads[i], NULL);

    time_t end_time = time(NULL);

    cout<<"time take by multithread : : "<<end_time - start_time<<endl;

    // Displaying the result matrix
    cout << "Multiplication of A and B" << endl;
    print_mat(matC);

    //unithread multiplication
    cout<<"\n\n unithread multiplication : \n"<<endl;
    //reset to zero all elements
    for(int i=0; i<MAX; i++)
        fill(matC[i], matC[i]+MAX, 0);

    start_time = time(NULL);
    unithread_multiplicatin();
    end_time = time(NULL);
    cout<<"time taken by unithread multiplication : "<<end_time - start_time<<endl;
	print_mat(matC);

    return 0;
}

