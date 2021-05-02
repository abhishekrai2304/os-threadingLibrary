#include "mto1.h"
#include <stdio.h>
#include <unistd.h>

mutexLock m1;
mthread t1, t2, t3;

void number_series(){
	long int k;
	thread_mutexLock(&m1);
	for(k = 0; k < 5; k++){
		printf("Number sequence is : %lu \n", k);
		printf("\n");
		yield();
	}
	thread_mutexUnlock(&m1);
	return;
}

void cube_of_number(){
	long int k;
	for (k = 0; k < 5; k++){
		printf("Cube is : \n%lu * %lu * %lu = %lu \n ", k, k, k, k*k*k);
		printf("\n");		
		yield();
	}
}

void square_of_number(){
	long int k;
	for (k = 0; k < 5; k++){
		printf("Square is :\n%lu * %lu = %lu \n  ", k, k, k*k);
		printf("\n");
		yield();
	}
}


void fibonaci_number(){
	long int k;
	int fibonaci[2] = { 0, 1 };
	printf("Fibonacci(0) = 0\nFibonnaci(1) = 1\n");
	for(k = 2; k < 15; k++){
		long int temp = fibonaci[0] + fibonaci[1];
		printf( "Fibonacci(%lu) = %lu\n", k, temp );
		printf("\n");		
		fibonaci[0] = fibonaci[1];
		fibonaci[1] = temp;
		yield();
	}
}



int main(){
	init();
	lockinit_m(&m1);
	create(&number_series);
	create(&cube_of_number);	
	exit_thread(NULL, &t3);
	create(&number_series);
	create(&square_of_number);
	//exit_thread(NULL, &t3);
	create(&cube_of_number);
	create(&fibonaci_number);
	join();

	return 0;
}
