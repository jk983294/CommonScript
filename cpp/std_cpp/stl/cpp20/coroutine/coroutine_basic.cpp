#include <coroutine>
#include <cstdint>
#include <exception>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>
#include <tuple>

using namespace std;

struct Event {
    int event_id{0};
};

class UserFacing {
public:
    class promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    class promise_type {  // associate the user-facing type with a promise type
    public:
        UserFacing get_return_object() {
            // construct an instance of the UserFacing to return to caller
            auto handle = handle_type::from_promise(*this);
            return UserFacing{handle};
        }

        std::suspend_never initial_suspend() {
            // specify whether the coroutine should start suspended, or run immediately
            // std::suspend_never causes the coroutine not to suspend itself on startup.
            return {};
        }
        void return_void() {
            // specify what to do when the coroutine returns normally
        }
        void unhandled_exception() {
            // specify what happens if an exception propagates out of the coroutine
        }
        std::suspend_always final_suspend() noexcept {
            // specify what happens when the coroutine terminates
            return {};
        }

        std::suspend_always await_transform(Event e) {
            printf("await_transform eid=%d\n", e.event_id);
            return {};
        }
    };

public:
    UserFacing(UserFacing &&rhs) : handle(rhs.handle) { rhs.handle = nullptr; }
    UserFacing &operator=(UserFacing &&rhs) {
        if (handle) handle.destroy();
        handle = rhs.handle;
        rhs.handle = nullptr;
        return *this;
    }
    ~UserFacing() {
        if (handle) handle.destroy();
    }

    void resume() { handle.resume(); }

private:
    handle_type handle;
    UserFacing(handle_type handle) : handle(handle) {}
    UserFacing(const UserFacing &) = delete;
    UserFacing &operator=(const UserFacing &) = delete;
};

UserFacing demo_coroutine() {
    std::cout << "hello" << std::endl;
    co_await Event{4};
    std::cout << "world" << std::endl;
    co_return;
}

void hello_demo() {
    UserFacing uf = demo_coroutine();
    std::cout << "we are back in main()" << std::endl;
    uf.resume();
}

class MyGen {
public:
    class promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    class promise_type {
    public:
        std::optional<int> yielded_value;
        std::optional<std::string> returned_value;
        std::exception_ptr exception = nullptr;

        std::suspend_always yield_value(int value) {
            yielded_value = value;
            return {};
        }
        void return_value(std::string value) { returned_value = value; }

        MyGen get_return_object() {
            auto handle = handle_type::from_promise(*this);
            return MyGen{handle};
        }
        std::suspend_always initial_suspend() { return {}; }
        void unhandled_exception() { exception = std::current_exception(); }
        std::suspend_always final_suspend() noexcept { return {}; }
    };

public:
    MyGen(MyGen &&rhs) : handle(rhs.handle) { rhs.handle = nullptr; }
    MyGen &operator=(MyGen &&rhs) {
        if (handle) handle.destroy();
        handle = rhs.handle;
        rhs.handle = nullptr;
        return *this;
    }
    ~MyGen() {
        if (handle) handle.destroy();
    }
    std::optional<int> next_value() {
        auto &promise = handle.promise();
        /**
         * init all internal member before we resume coroutine
         */
        promise.yielded_value = std::nullopt;
        promise.exception = nullptr;

        if (!handle.done())  // after final_suspend() called, done() return true, you should not resume it again!!!
            handle.resume();
        if (promise.exception) std::rethrow_exception(promise.exception);
        return promise.yielded_value;
    }

    std::optional<std::string> final_result() { return handle.promise().returned_value; }

private:
    handle_type handle;
    MyGen(handle_type handle) : handle(handle) {}
    MyGen(const MyGen &) = delete;
    MyGen &operator=(const MyGen &) = delete;
};

MyGen demo_mygen_coroutine() {
    co_yield -42;
    for (int i = 1; i <= 3; i++) co_yield i;
    co_yield 42;
    co_return "goodbye";
}

void gen_demo() {
    MyGen demo_instance = demo_mygen_coroutine();
    while (std::optional<int> value = demo_instance.next_value()) std::cout << "got integer " << (*value) << std::endl;

    if (std::optional<std::string> result = demo_instance.final_result())
        std::cout << "final result = \"" << *result << "\"" << std::endl;
}

int main() {
    hello_demo();
    gen_demo();
}