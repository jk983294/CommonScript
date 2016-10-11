#include <iostream>
#include <future>
#include <thread>

using namespace std;

/**
 * packaged_task wraps any Callable target
 * (function, lambda expression, bind expression, or another function object)
 * so that it can be invoked asynchronously.
 * Its return value or exception thrown is stored in a shared state which can be accessed through std::future objects.
 */

int f(int x, int y) {
    return x + y;
}

void task_lambda() {
    std::packaged_task<int(int,int)> task([](int a, int b) {
        return a + b;
    });
    std::future<int> result = task.get_future();
    task(2, 9);
    std::cout << "task_lambda:\t" << result.get() << endl;
}

void task_bind() {
    std::packaged_task<int()> task(std::bind(f, 2, 11));
    std::future<int> result = task.get_future();
    task();
    std::cout << "task_bind:\t" << result.get() << endl;
}

void task_thread() {
    std::packaged_task<int(int,int)> task(f);
    std::future<int> result = task.get_future();
    std::thread task_td(std::move(task), 2, 10);
    task_td.detach();
    std::cout << "task_thread:\t" << result.get() << endl;
}

int main() {
    task_lambda();
    task_bind();
    task_thread();
    return 0;
}