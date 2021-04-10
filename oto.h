#define _GNU_SOURCE 
#define error_malloc 1
#define error_clone 2
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

typedef pid_t mthread;
typedef struct thread_t{
    char *stack;
    mthread tid;

}thread_t;

typedef struct spinLock{
    int val;
}spinLock;

void func(void* arg);
int thread_create(mthread *t, void *func, int argc, char** argv);
// int thread_join(thread_t *t, void **retval);
int thread_join(mthread *t);
void thread_kill(mthread t,  int sig);
int thread_spinLock(spinLock *lock);
int thread_spinUnlock(spinLock *lock);
int lockValue(spinLock *lock);