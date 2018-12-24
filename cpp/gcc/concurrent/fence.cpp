#include <iostream>

using namespace std;

/**
 * lfence stalls instruction issue until all instructions before the lfence are completed.
 *
 * mfence specifically waits for all preceding memory reads to be brought fully into the destination register,
 * and waits for all preceding writes to become globally visible,
 * but does not stall all further instructions as lfence would.
 *
 * sfence does the same for only stores, flushes write combiner, and ensures that
 * all stores preceding the sfence are globally visible before allowing any stores following the sfence
 * to begin execution.
 */

#define MemoryBarrier1() asm volatile("lfence" ::: "memory")
#define MemoryBarrier2() asm volatile("mfence" ::: "memory")
#define MemoryBarrier3() asm volatile("sfence" ::: "memory")

int main() {
    cout << "hello" << endl;
    MemoryBarrier1();
    MemoryBarrier2();
    MemoryBarrier3();
    return 0;
}
