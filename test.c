#include<stdio.h>
typedef struct lock{
    int val;
}lock;
int main(){
    lock l1;
    while(l1.val != 0);
    printf("runs: %d", l1.val); 
       return 0;
}