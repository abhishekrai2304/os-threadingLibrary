#include "mto1.h"

static spthread thread_list[MAX_THREAD];  

static int cur_exe_thread = 0;            //This line is for currently executing thread

static int num_active_thread = 0;         //This line is for number of the  active thread

static int within_thread = 0;			

static ucontext_t ctext;

//setting the thread in inactive state

void spthread_init(){				

	int j;
	for(j = 0; j < MAX_THREAD; ++j){		
		thread_list[j].state_a = 0;
	}
	return;
}


int spthread_create(void (*func)(void))  		
{
	if(num_active_thread == MAX_THREAD){
		 return limitErr;
	}
	getcontext(&thread_list[num_active_thread].context);
	thread_list[num_active_thread].context.uc_link = 0;
	thread_list[num_active_thread].stack = malloc( STACK_SIZE );
	thread_list[num_active_thread].context.uc_stack.ss_sp = thread_list[num_active_thread].stack;
	thread_list[num_active_thread].context.uc_stack.ss_size = STACK_SIZE;
	thread_list[num_active_thread].context.uc_stack.ss_flags = 0;
	if (thread_list[num_active_thread].stack == 0){
		printf("Error: Could not allocate stack.\n");
		return mallErr;
	}
	makecontext(&thread_list[num_active_thread].context, (void (*)(void)) &thread_begin, 1, func);
	++num_active_thread;
	return noErr;
}

















