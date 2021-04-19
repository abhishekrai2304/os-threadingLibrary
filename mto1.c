#include "mto2.h"
static int cur_exe_thread = 0;          

static int num_active_thread = 0;         
static int within_thread = 0;			


ucontext_t maincontext;
thread_tcb main_t;
thread_tcb *current;
queue ready_q; 


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
//void thread_init(){				

//	int j;
//	for(j = 0; j < MAX_THREAD; ++j){		
//		thread_list[j].state = 0;
//	}
//	return;
//}



int create_t (int (*thread_run)(int*), void *arguments)  {
	int arg;
	thread_tcb *thread;
	thread = (thread_tcb*)malloc(sizeof(thread_tcb));
	
	thread->thread_id = size_q(&ready_q);
	if ( getcontext(&(thread->uc)) == -1 ) {
		printf("Context can not be fetched due to error\n");
		exit(EXIT_FAILURE);
	}
        
	thread->uc.uc_link = &maincontext;
	thread->uc.uc_stack.ss_sp = malloc(SIGSTKSZ);
	thread->uc.uc_stack.ss_size = SIGSTKSZ;
 	makecontext(&(thread->uc), (void (*) ()) thread_run, 2, arg);
	enqueue(&ready_q, thread);
	return 0 ; 
}



int thread_run (int* arg) {
  printf("Child is here");
	
}
/*
int spthread_join(){
	int pending_thread = 0;
	if(within_thread){
		pending_thread = 1;
	}
	while(num_active_thread > pending_thread){	
		spthread_yield();
	}
	return noErr;
}


void spthread_yield(){
	if(within_thread){
		swapcontext(&thread_list[cur_exe_thread].context, &ctext);
	}
	else{
		if(num_active_thread == 0)
			return; 
		cur_exe_thread = (cur_exe_thread + 1) % num_active_thread;
		within_thread = 1;
		swapcontext(&ctext, &thread_list[cur_exe_thread].context);	
		within_thread = 0;
		if(thread_list[cur_exe_thread].state_a == 0){
			free(thread_list[cur_exe_thread].stack);
			--num_active_thread;
			if(cur_exe_thread != num_active_thread){
				thread_list[cur_exe_thread] = thread_list[num_active_thread];
			}
			thread_list[num_active_thread].state_a = 0;
		}
	}
	return;
}
*/
void main(){
	thread_tid *id_thread;
	thread_tcb *tcb;
	init_t(10);
	id_thread = (thread_tid*)malloc(sizeof(thread_tid));
	tcb = (thread_tcb*)malloc(sizeof(thread_tcb));
	id_thread->thread_id = create_t(thread_run, tcb->arg);
	printf("Thread identification of child is: %d" ,id_thread->thread_id);
	printf("\n");
	printf("Thread identification of parent is: %d", getppid());


}


















