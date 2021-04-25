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

#define noErr  0
#define limitErr 1
#define mallErr	2

#define MAX_THREAD 10

//#define STACK_SIZE (1024*1024)



typedef struct {
	int thread_id; 
	ucontext_t uc;
	void *retval;
	void *arg;
} thread_tcb;

typedef struct thread_tid{
	int thread_id;
}thread_tid;

typedef struct node {
	struct node *next;
	thread_tcb *data;
} node; 

typedef struct queue {
	struct node *front;
	struct node *rear;
	int count;
} queue; 

typedef struct lock_struct{
	int value;
}thread_l;

typedef struct mto1{
	ucontext_t context;
	int state_a;
	void *stack;
}threadm;




//void init_t(queue *que); 
void init();
void begin(void (*func)(void));
int create(void (*func)(void));

int size_q(queue *que); 

int enqueue (queue *q, thread_tcb *thread); 
int join();
void yield();
void lockinit(thread_l *);
int lock(thread_l *);
int unlock(thread_l *);
int value(thread_l *);



//void init();
//void begin(void (*func)(void));
//int create(void (*func)(void));





//#define STACK_SIZE (1024*1024)















