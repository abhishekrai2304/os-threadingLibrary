#define _GNU_SOURCE

#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <linux/sched.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ucontext.h>
#include <signal.h>
#define mallErr 2
#define limitErr 1
//#define mallErr 2
#define er 0
#define DEFUNCT 3
#define SYS_exit (1)

#define MAX_THREAD 10

//#define STACK_SIZE (1024*1024)
typedef pid_t mthread;

typedef struct thread_thr{
	void *result;
	mthread tid;
	char *stack;
}thread_thr;


typedef struct{
	int thread_id; 
	ucontext_t uc;
	void *retval;
	void *arg;
}thread_tcb;

typedef struct thread_tid{
	int thread_id;
}thread_tid;

typedef struct node{
	struct node *next;
	thread_tcb *data;
}node; 

typedef struct queue{
	struct node *front;
	struct node *rear;
	int count;
}queue; 

typedef struct lock_struct{
	int value;
}thread_l;

typedef struct mutex_lock{
	int value;
}mutexLock;

typedef struct mto1{
	ucontext_t context;
	int state_a;
	void *stack;
}threadm;


typedef struct thread_tc{
	pid_t thread_id;
	struct thread_tc *prev, *next;
	int state;
}thread_tc;





//void init_t(queue *que); 
void init();
void begin(void (*func)(void));
int create(void (*func)(void));

int size_q(queue *que); 

int enqueue (queue *q, thread_tcb *thread); 
int join();
void yield();
void lockinit(thread_l *);
int spin_lock(thread_l *);
int spin_unlock(thread_l *);
int value(thread_l *);
int mutexLockValue(mutexLock *lock);
void lockinit_m(mutexLock *lock);
int thread_mutexLock(mutexLock *lock);
int thread_mutexUnlock(mutexLock *lock);
void exit_thread();




//void init();
//void begin(void (*func)(void));
//int create(void (*func)(void));





//#define STACK_SIZE (1024*1024)















