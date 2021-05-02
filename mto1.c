#include "mto1.h"
static int cur_exe_thread = 0;  
static threadm t_list[MAX_THREAD];         

static int num_active_thread = 0;         
static int within_thread = 0;	
static ucontext_t ctext;		


ucontext_t maincontext;
thread_tcb main_t;
thread_tcb *current;
queue ready_q; 


mutexLock m_lock;
void func(void *arg)
{
  thread_mutexLock(&m_lock);
  for (int k = 0; k < 5; k++)
  {
    printf("%d\n", k);
  
  }
  thread_mutexUnlock(&m_lock);

}


int size_q (queue *que) {
        return que->count;
}

void init_q (queue *que) {
        que->front = que->rear = NULL;
	que->count = 0;
}

int enqueue (queue *q, thread_tcb *thread) {
        node *temp = (node *) malloc(sizeof(node));
        if (temp == NULL) {
		return 0;
	}
	temp->data = thread;
	temp->next = NULL;

        if (q->rear) {
                q->rear->next = temp;
                q->rear = temp;
        }
        else
        {
                q->rear = temp;
                q->front = temp;
        }
	++(q->count);

        return 1;
}


void init_t (long period) {

	init_q(&ready_q);
	main_t.thread_id = -1;
	if ( getcontext(&(main_t.uc)) == -1) {
		printf("Context can not be fetched due to some issue\n");
		exit(EXIT_FAILURE);
	}	
	current = &main_t; 

}
void init(){				

	int j;
	for(j = 0; j < MAX_THREAD; ++j){		
		t_list[j].state_a = 0;
	}
	return;
}

int create(void (*func)(void))  		
{
	if(num_active_thread == MAX_THREAD){
		 return limitErr;
	}
	getcontext(&t_list[num_active_thread].context);
	t_list[num_active_thread].context.uc_link = 0;
	t_list[num_active_thread].stack = malloc( 1024*1024 );
	t_list[num_active_thread].context.uc_stack.ss_sp = t_list[num_active_thread].stack;
	t_list[num_active_thread].context.uc_stack.ss_size = 1024*1024;
	t_list[num_active_thread].context.uc_stack.ss_flags = 0;
	if (t_list[num_active_thread].stack == 0){
		printf("Error: Could not allocate stack.\n");
		return mallErr;
	}
	makecontext(&t_list[num_active_thread].context, (void (*)(void)) &begin, 1, func);
	++num_active_thread;
	return 0;
}



int thread_run (int* arg) {
  printf("Child is here");
	
}

void begin(void (*func)(void)){    
	t_list[cur_exe_thread].state_a = 1;
	func();
	t_list[cur_exe_thread].state_a = 0;
	yield();
}

int join(){
	int pending_thread = 0;
	if(within_thread){
		pending_thread = 1;
	}
	while(num_active_thread > pending_thread){	
		yield();
	}
	return 0;
}

void yield(){
	if(within_thread){
		swapcontext(&t_list[cur_exe_thread].context, &ctext);
	}
	else{
		if(num_active_thread == 0)
			return; 
		cur_exe_thread = (cur_exe_thread + 1) % num_active_thread;
		within_thread = 1;
		swapcontext(&ctext, &t_list[cur_exe_thread].context);	
		within_thread = 0;
		if(t_list[cur_exe_thread].state_a == 0){
			free(t_list[cur_exe_thread].stack);
			--num_active_thread;
			if(cur_exe_thread != num_active_thread){
				t_list[cur_exe_thread] = t_list[num_active_thread];
			}
			t_list[num_active_thread].state_a = 0;
		}
	}
	return;
} 

void exit_thread(void *retval, mthread *thr){
	thread_thr t;
	t.tid = *thr;
	t.result = retval;
	syscall(SYS_exit);
}


void lockinit(thread_l *lock){
	lock->value = 0;
}

int lock_value(thread_l *lock){
	if(lock->value == 0)
		return 0;
	else
		return 1;
}


int spin_lock(thread_l *lock){
	while(lock_value(lock) != 0)
		join();
	lock->value = 1;
	return 0;
}


int spin_unlock(thread_l *lock){
	lock->value = 0;
	return 0;
}

void lockinit_m(mutexLock *lock){
	lock -> value = er;
}


int mutex_lock_value(mutexLock *lock){
	if(lock->value == 0)
		return 0;
	else
		return 1;
}


int thread_mutexLock(mutexLock *lock){
	while(mutex_lock_value(lock) != 0)
		
		join();
		sleep(2);
	lock->value = 1;
	return 0;
}


int thread_mutexUnlock(mutexLock *lock){
	lock->value = 0;
	return 0;
}

int thread_kill(mthread t, int sig){
	if(sig == 0){
		return 0;
	}
	pid_t tgid = getpid();
	kill(tgid, SIGINT);
	return 0;
}
















