#include <thread>
#include <future>
#include <iostream>
#include <atomic>
#include <cassert>


/**
 * memory model
 * http://wilburding.github.io/blog/2013/04/07/c-plus-plus-11-atomic-and-memory-model/
 * memory_order_release, 编译器保证不会把其后的写操作移到它后边, 否则其他线程就看不到这个修改了
 * memory_order_acquire, 不会把其后的读操作移到它前面, 否则读到的就是旧数据
 * memory_order_relaxed, 说明这个操作除了是原子的外,周围的操作随便移动，比较适合做计数器
 * memory_order_acq_rel, 基本是 memory_order_acquire 和 memory_order_release 的合体
 * memory_order_scq_cst, memory_order_acq_rel的加强版, 除了有acq_rel语义, 还保证是sequencially-consistent
 * memory_order_consume, memory_order_acquire的弱化版, 它只保证不把跟当前load的变量有依赖的变量reorder, 没依赖关系的随便移动
 */

std::atomic<int> flag(0);
int data = 0;

void thread1()
{
    data = 1;
    flag.store(1, std::memory_order_release);
}
void thread2()
{
    while(flag.load(std::memory_order_acquire) == 0);
    assert(data == 1);
}

class Foo{};

int main() {
    std::atomic<bool> b;
    bool x1=b.load(std::memory_order_acquire);
    b.store(true);
    x1=b.exchange(false, std::memory_order_acq_rel);

    Foo some_array[5];
    std::atomic<Foo*> p(some_array);
    Foo* x=p.fetch_add(2);                          // p加2，并返回原始值
    assert(x==some_array);
    assert(p.load()==&some_array[2]);
    x=(p-=1);                                       // p减1，并返回原始值
    assert(x==&some_array[1]);
    assert(p.load()==&some_array[1]);
    return 0;
}