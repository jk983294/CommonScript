#include <linux/futex.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <iostream>
#include <thread>

using namespace std;

/**
 * FUTEX_PRIVATE_FLAG synchronization only between threads of the same process
 * FUTEX_WAIT_PRIVATE / FUTEX_WAKE_PRIVATE
 *
 * FUTEX_WAIT sleep if val1 == *uaddr, if no equal, then fail immediately with error EAGAIN
 * FUTEX_WAKE wakes at most val of the waiters that are waiting at address uaddr
 */

long sys_futex(void *uaddr, int op, int val1, struct timespec *timeout, void *uaddr2, int val3) {
    return syscall(SYS_futex, uaddr, op, val1, timeout, uaddr2, val3);
}

int data = 1;

void thread1() {
    cout << "thread1 start, wait for wake up by thread2\n";
    sys_futex(&data, FUTEX_WAIT_PRIVATE, data, nullptr, nullptr, 0);
    sleep(2);
    cout << "thread1 after wake up by thread2\n";
}

void thread2() {
    sleep(2);
    cout << "thread2 before send wake up to thread1\n";
    sys_futex(&data, FUTEX_WAKE_PRIVATE, 1, nullptr, nullptr, 0);
    cout << "thread2 after send wake up to thread1\n";
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);
    t1.join();
    t2.join();
    cout << "end test\n";
    return 0;
}
