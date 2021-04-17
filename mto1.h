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
#define noErr  0
#define limitErr 1
#define mallErr	2

#define MAX_THREAD 10
#define STACK_SIZE (1024*1024)

typedef struct mto1{
	ucontext_t context;
	int state_a;
	void *stack;
}thread1;


void spthread_init();
int spthread_create(void (*func)(void));


