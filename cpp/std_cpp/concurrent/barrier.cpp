#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

#define ACCESS_ONCE(x) (*(volatile typeof(x) *)&(x))
// READ_ONCE use smp_read_barrier_depends()

int shared_variable = 0;
int run = 1;

inline void cpu_relax() {
    // asm volatile ("yield" ::: "memory"); // yield for AMD64 instruction gives better perf
    asm volatile ("" ::: "memory"); // barrier
}

void thread1(size_t reader_name) {
    while (run) {
        cpu_relax();
    }
    cout << "thread1=" << reader_name << " value=" << shared_variable << endl;
}

void thread2(size_t writer_name) {
    shared_variable = 42;
    cout << "writer " << writer_name << " " << shared_variable << endl;
    run = 0; // notify reader
}

int main(){
    thread thd1(thread1, 1);
    sleep(5);
    thread thd2(thread2, 2);

    thd1.join();
    thd2.join();
    return 0;
}

