# make deals starts from all command then flow the dependencies like dfs of dependencies
#target: dependencies
#[tab] system command

# specify the compiler
CC=g++

# specify options for the compiler
CFLAGS=-c -Wall

all: hello

#linking command
hello: main.o factorial.o hello.o
	g++ main.o factorial.o hello.o -o hello

main.o: main.cpp
	g++ -c main.cpp

factorial.o: factorial.cpp
	g++ -c factorial.cpp

hello.o: hello.cpp
	g++ -c hello.cpp

clean:
	rm -rf *.o
