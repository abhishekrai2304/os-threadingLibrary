#include "oto.h"
int done = 0;
pid_t parent;

void func(void *arg){
  // printf("I am don");
  char *buf = (char *)arg;
  printf("Child sees buf = \"%s\"\n", buf);
  strcpy(buf, "hello from child");
}
int thread_create(thread_t *t, void *func, int argc, char **argv){
  
  const int STACK_SIZE = 65536;
  t->stack = malloc(STACK_SIZE);
  if (!t->stack){
    // perror("malloc");
    // exit(1);
    return error_malloc;
  }

  unsigned long flags = 0;
  flags |= CLONE_VM;
  char buf[100];
  strcpy(buf, "hello from parent");
  if (clone(func, t->stack + STACK_SIZE, flags | SIGCHLD, buf) == -1){
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
  done = 1;
  return 0;
}

int thread_join(thread_t *t, void **retval){
  pid_t tid = gettid();
  int status;
  // if(tid != parent){
  //   wait(&status);
  // }
    wait(&status);
    printf("Child exited with status %d\n", status);
    free(t->stack);
    return 0;
  
}

void thread_init(thread_t *t){
  t->stack = NULL;
}

int main(int argc, char **argv){
  parent = getpid();
  thread_t t1;
  thread_init(&t1);
  thread_create(&t1, &func, argc, argv);
  thread_join(&t1, NULL);
  return 0;
}