#include <thread>
#include <mutex>
#include <stack>
#include <iostream>
#include <exception>
#include <memory>

struct EmptyStackException : std::exception
{
    const char* what() const throw()
    {
        return "empty stack";
    }
};

template<typename T>
class ThreadSafeStack
{
private:
    std::stack<T> data;
    mutable std::mutex m;
public:
    ThreadSafeStack(){}
    ThreadSafeStack(const ThreadSafeStack & other)
    {
        std::lock_guard<std::mutex> lock(other.m);                  // lock other's mutex in case other be modified
        data=other.data;
    }
    ThreadSafeStack & operator=(const ThreadSafeStack &) = delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(new_value);
    }
    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) throw EmptyStackException();
        std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
        data.pop();
        return res;
    }
    void pop(T& value)
    {
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) throw EmptyStackException();
        value=data.top();
        data.pop();
    }
    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};

int main()
{
    ThreadSafeStack<int> si;
    si.push(5);
    si.pop();
    if(!si.empty())
    {
        int x;
        si.pop(x);
    }
    return 0;
}