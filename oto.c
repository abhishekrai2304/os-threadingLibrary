#include "oto.h"
static pid_t parent_pid;
int done = 0;
pid_t parent;
int val1 = 0;
static int num_thread = 0;
static thread_t th[5];
spinLock l1;
mutexLock ml1;
void func(void *arg)
{
  thread_mutexLock(&ml1);
  for (int i = 0; i < 5; i++)
  {
    printf("%d\n", i);
  
  }
  //thread_spinUnlock(&l1);
  thread_mutexUnlock(&ml1);

}
int thread_create(mthread *th, void *func, int argc, char **argv)
{
  thread_t t;
  const int STACK_SIZE = 65536;
  t.stack = malloc(STACK_SIZE);
  if (!t.stack)
  {
    // perror("malloc");
    // exit(1);
    
    return error_malloc;
  }

  unsigned long flags = 0;
  flags |= CLONE_VM;
  char buf[100];
  strcpy(buf, "hello from parent");
  
  if (t.tid = clone(func, t.stack + STACK_SIZE, flags | SIGCHLD, buf) == -1)
  {
    // perror("clone");
    // exit(1);
    return error_clone;
  }

  // int status;
  // if (wait(&status) == -1){
  //   perror("wait");
  //   exit(1);
  // }

  // printf("Child exited with status %d. buf = \"%s\"\n", status, buf);
  
  *th = t.tid;
  num_thread--;
  return done++;
}

int thread_join(mthread *th){				//function join
	thread_t *t;
  pid_t tid;
	int i;
	int pending_thread = 0;
	tid = getpid();
	if(tid != parent_pid){
		return 101;
	}
	while(num_thread >  pending_thread){
		tid = wait(0);
		if(tid == -1){
			printf("Error: Wait syscall failed\n");
			exit(1);			
		}
		for(i = 0; i < num_thread; ++i){
			if(t->tid == tid){
				num_thread--;
				free(t->stack);
				// if(i != num_thread){
				// 	thread_list[i] = thread_list[num_thread];
				// }
				i = -1;
				break;
			}

		}
		if(i == num_thread){
			printf("Error: Unable to find thread id\n");
		}	
	}
	return 0;
}

void thread_kill(mthread t,  int sig){
  if(sig == 0){
        //printf("kill success");
  }
  pid_t tgid = getpid();
  int i = tgkill(tgid, t, sig);
}
int lockValue(spinLock *lock){
  if(lock->val == 0)
    return 0;
  else
    return 1;
}

int thread_spinLock(spinLock *lock){
  while(lockValue(lock) != 0);
    lock->val = 1;
  return 0;

 
}

int thread_spinUnlock(spinLock *lock){
  lock->val = 0;
  return 0;
}
int mutexLockValue(mutexLock *lock){
  if(lock->val == 0)
    return 0;
  else 
    //sleep(2);
  return 1;
}
int thread_mutexLock(mutexLock *lock){
  while(mutexLockValue(lock) != 0)
    sleep(2);
  lock->val = 1;
  return 0;
}
int thread_mutexUnlock(mutexLock *lock){
  lock->val = 0;
  return 0;
}
int main(int argc, char **argv)
{
  int v;
  int *ptr[2];
  int ret1 = 69;
  parent = getpid();
  mthread t1, t2;
  // thread_init(&t1);
  // thread_init(&t2);
  v = thread_create(&t1, &func, argc, argv);
  thread_kill(t1,  0);
 v = thread_create(&t1, &func, argc, argv);
  //thread_join(&t1);
//  thread_kill(t1, SIGKILL);
  //printf("after kill call");
  //thread_join(&t2, NULL);
  //thread_exit(&ret1);
  //printf("%d\n", val1);
  return 0;
}