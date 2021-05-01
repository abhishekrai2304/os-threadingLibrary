#include "oto.h"

static pid_t parent_pid;

int done = 0;
pid_t parent;
int val1 = 0;

static int num_thread = 0;
static thread_t th[5];
spinLock l1;
mutexLock ml1;

mthread t1, t2, t3;

// inline int tgkill(int tgid, int tid, int sig) {
//     return syscall(SYS_tgkill, tgid, tid, sig);
// }

static inline int futex(int *uaddr, int futex_op, int val) {
    return syscall(SYS_futex, uaddr, futex_op, val, NULL, NULL, 0);
}



int thread_create(mthread *th, void *func)
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

  unsigned long flags = 0, thread;
  flags |= CLONE_VM;
  thread |= CLONE_THREAD;

  char buf[100];
  strcpy(buf, "hello from parent");
  
if (t.tid = clone(func, t.stack + STACK_SIZE,  SIGCHLD | CLONE_FS | CLONE_FILES |\
 CLONE_SIGHAND | CLONE_VM, buf) == -1)
  {
    perror("clone");
    // exit(1);

    return error_clone;
  }

 
  
  *th = t.tid;
  num_thread--;
  
  return done++;
}


void thread_exit(void *retval, mthread *th){
  thread_t t;
  t.tid = *th;
  t.result = retval;
  // sys_exit();
  syscall(SYS_exit);
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



int thread_kill(mthread t,  int sig){
  if(sig == 0){
        
        return 0;
  }
  pid_t tgid = getpid();
  // int err = tgkill(tgid, t, sig);
  // if(err == -1){
  //   return errno;
  // }
 // signal(SIGINT, handler);
  kill(tgid, SIGINT);
  return 0;
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

