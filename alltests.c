#include"oto.h"
#include<stdio.h>
spinLock l1;
mthread t1, t2, t3;

void func2(void *arg){

  printf("\n******************** Test for Cube: ********************\n");
  thread_spinLock(&l1);
  for(int i = 0; i < 10; i++)
  printf("%d * %d * %d = %d\n", i, i, i, i*i*i);
  thread_spinUnlock(&l1);
  thread_kill(t3, SIGINT);
}

void func1(void *arg){

  printf("\n******************** Test for Nums: ********************\n");
	thread_spinLock(&l1);
  for (int i = 0; i < 20; i++){
    printf("Hello this is No %d \n", i);
  }
  thread_spinUnlock(&l1);
}

void func(void *arg){	
  
  printf("\n******************** Test for factorial: ********************\n");
  thread_spinLock(&l1);
  int fact = 1;
  for (int i = 1; i < 5; i++){
    fact = fact * i;
  }
  printf("Factorial of 4 is %d\n", fact);
  thread_spinUnlock(&l1);
}


int main(int argc, char **argv){
	int v, m, n;
	
	
	v = thread_create(&t1, &func);
	
	m = thread_create(&t2, &func1);
	
 	n = thread_create(&t3, &func2);

  thread_join(&t1);
  thread_join(&t2);
  thread_join(&t3);
  thread_exit(NULL, &t2);
  printf("after exit");

  return 0;
}


// int main(int argc, char **argv)
// {
//   int v1, v2;
//   int *ptr[2];
//   int ret1 = 69;
//   parent = getpid();
//   v1 = thread_create(&t3, &func);

 
//   v2 = thread_create(&t1, & func1);
//   thread_join(&t1);
//   thread_join(&t3);
 
//  thread_exit(NULL, &t2);
//  printf("after exit");
//   return 0;
// }
