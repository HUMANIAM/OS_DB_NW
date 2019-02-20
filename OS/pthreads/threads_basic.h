#ifndef THREADS_BASIC_H_INCLUDED
#define THREADS_BASIC_H_INCLUDED

/**
- threads operation : create, terminate, sync, shedule, data management, memory management
- a thread doesn't maintain a list about the created threads, nor deos it know the thread that created it.
- all threads within a process share the same address space.

- Resources shared among threads within the same process
    * process instructions
    * most data
    * open files (file descriptors)
    * signals and signal handlers
    * current working directory
    * user and group id

- private resources for every thread
    * thread ID
    * set of registers, stack pointer
    * stack for local variables, return address
    * signal mask
    * priority
    * return value : errno

- pthread functions returns "0" if the function executed without any errors

*/

//print msg
void* print_msg(void*);

//create some threads
int create_some_threads(void);
#endif // THREADS_BASIC_H_INCLUDED
