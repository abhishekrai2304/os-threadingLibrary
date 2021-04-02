#define _GNU_SOURCE 
#include<stdio.h>
#include<sys/types.h>
#include<sched.h>
#include<linux/sched.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<bits/sched.h>
#include<sys/wait.h>
#include<sys/utsname.h>
#include<unistd.h>

#define error_malloc 1
#define error_clone 2
typedef struct thread_t{
    char *stack;
    //ttid tid;

}thread_t;

void func(void* arg);
int thread_create(thread_t *t, void *func, int argc, char** argv);
int thread_join(thread_t *t, void **retval);