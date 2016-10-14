#include <iostream>
#include <thread>
#include <exception>
#include <stdexcept>


/**
 * exception_ptr type that allows to transport exceptions between threads
 * unhandled exception in thread will crash whole process
 */

std::exception_ptr ptr = nullptr;

void f()
{
    try
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        throw std::runtime_error("to be passed between threads");
    }
    catch(...)
    {
        ptr = std::current_exception();
    }
}

int main()
{
    std::thread t(f);
    t.join();

    if (ptr) {
        try{
            std::rethrow_exception(ptr);
        }
        catch(const std::exception &ex)
        {
            std::cerr << "thread exited with exception: " << ex.what() << std::endl;
        }
    }
    return 0;
}