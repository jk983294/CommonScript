#include <thread>
#include <future>
#include <iostream>
#include <atomic>
#include <utility>

std::atomic<int> data;
void do_work()
{
    data.fetch_add(5, std::memory_order_relaxed);
    data.fetch_sub(3, std::memory_order_relaxed);
    data++;
    data--;
    --data;
    ++data;

    data += 1;
    data -= 1;
}

struct A {
    int a[100];
};
struct B {
    int x, y;
};

int main()
{
    std::cout << std::boolalpha
        //<< "std::atomic<A> is lock free? "
        //<< std::atomic<A>{}.is_lock_free() << std::endl       // A will failed because it is not primitive object
        << "std::atomic<B> is lock free? "
        << std::atomic<B>{}.is_lock_free() << std::endl;
    std::atomic<int> ai(5);
    int expected = 5;
    bool exchanged= ai.compare_exchange_strong(expected, 3);
    std::cout << "ai= " << ai << "  exchanged= " << std::boolalpha << exchanged << std::endl;

    std::thread th1(do_work);
    std::thread th2(do_work);
    std::thread th3(do_work);
    std::thread th4(do_work);
    std::thread th5(do_work);

    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();

    std::cout << "result:" << data << std::endl;
    return 0;
}