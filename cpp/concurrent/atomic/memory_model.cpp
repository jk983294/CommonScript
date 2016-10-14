#include <thread>
#include <future>
#include <iostream>
#include <atomic>
#include <cassert>


/**
 * memory model
 * http://wilburding.github.io/blog/2013/04/07/c-plus-plus-11-atomic-and-memory-model/
 * memory_order_release, ��������֤���������д�����Ƶ������, ���������߳̾Ϳ���������޸���
 * memory_order_acquire, ��������Ķ������Ƶ���ǰ��, ��������ľ��Ǿ�����
 * memory_order_relaxed, ˵���������������ԭ�ӵ���,��Χ�Ĳ�������ƶ����Ƚ��ʺ���������
 * memory_order_acq_rel, ������ memory_order_acquire �� memory_order_release �ĺ���
 * memory_order_scq_cst, memory_order_acq_rel�ļ�ǿ��, ������acq_rel����, ����֤��sequencially-consistent
 * memory_order_consume, memory_order_acquire��������, ��ֻ��֤���Ѹ���ǰload�ı����������ı���reorder, û������ϵ������ƶ�
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
    Foo* x=p.fetch_add(2);                          // p��2��������ԭʼֵ
    assert(x==some_array);
    assert(p.load()==&some_array[2]);
    x=(p-=1);                                       // p��1��������ԭʼֵ
    assert(x==&some_array[1]);
    assert(p.load()==&some_array[1]);
    return 0;
}