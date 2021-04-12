#include "mto.h"
void thread_init(mthread *th){
    thread_t t;
    t.stack = 0;
    t.tid = 0;

}
int main(){
    mthread t1;
    thread_init(&t1);
    return 0;
}