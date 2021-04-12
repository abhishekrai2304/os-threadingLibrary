#include<signal.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>

typedef enum thread_states{
    RUNNING = 0,
    READY,
    FINISHED,
    WAITING,

}thread_state;

typedef pid_t mthread;

typedef struct thread_t{
    mthread tid;
    thread_state ts;
    void *stack;
}thread_t;

typedef struct spinLock{
    int val;
}spinLock;

void thread_init(mthread *t);

