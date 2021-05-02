#include "mto1.h"
#include <stdio.h>
#include <unistd.h>

thread_l l1;
mutexLock m1;
mthread t1, t2, t3;

void number_series(){
	long int k;
	spin_lock(&l1);
	for(k = 0; k < 5; k++){
		printf("Number sequence is : %lu \n", k);
		printf("\n");
		yield();
	}
	
	spin_unlock(&l1);
	thread_kill(t3, SIGINT);
	printf("Executed");
	//return;
}

void fibo(){
	long int i;
	long int fib[2] = { 0, 1 };
	printf("Fibonacci(0) = 0\nFibonnaci(1) = 1\n");
	for(i = 2; i < 15; ++i){
		long int nextFib = fib[0] + fib[1];
		printf("Fibonacci(%lu) = %lu\n", i, nextFib );
		printf("\n");
		fib[0] = fib[1];
		fib[1] = nextFib;
		yield();
	}
}

void cube_of_number(){
	long int k;
	for (k = 0; k < 5; k++){
		printf("Cube of a number is :%lu * %lu * %lu = %lu ", k, k, k, k*k*k);
		printf("\n");
		yield();
	}
}

int main(){
	init();
	lockinit(&l1);
	create(&number_series);
	create(&cube_of_number);
	create(&number_series);
	create(&fibo);
	create(&cube_of_number);
	join();
	exit_thread(NULL, &t3);
        printf("after exit \n");
	return 0;
}
