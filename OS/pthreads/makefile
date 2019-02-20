# specify the compiler
CC=gcc

# specify options for the compiler
CFLAGS = -c -Wall

all : threads

#linker step
threads : main.o threads_basic.o matrix_multiplication_threads.o
	$(CC) -pthread  main.o threads_basic.o matrix_multiplication_threads.o -o threads

main.o: main.c
	$(CC) -pthread $(CFLAGS) main.c

matrix_multiplication_threads.o: matrix_multiplication_threads.c
	$(CC) -pthread $(CFLAGS) matrix_multiplication_threads.c

threads_basic.o : threads_basic.c
	$(CC) -pthread $(CFLAGS)   threads_basic.c

clean :
	rm -rf *.o threads

