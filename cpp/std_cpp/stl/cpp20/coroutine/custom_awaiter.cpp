#include <coroutine>
#include <iostream>

class UserFacing {
public:
    class promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    class promise_type {
    public:
        UserFacing get_return_object() {
            auto handle = handle_type::from_promise(*this);
            return UserFacing{handle};
        }
        std::suspend_always initial_suspend() { return {}; }
        void return_void() {}
        void unhandled_exception() {}
        std::suspend_always final_suspend() noexcept { return {}; }
    };

private:
    handle_type handle;
    UserFacing(handle_type handle) : handle(handle) {}

    UserFacing(const UserFacing &) = delete;
    UserFacing &operator=(const UserFacing &) = delete;

public:
    bool resume() {
        if (!handle.done()) handle.resume();
        return !handle.done();
    }

    UserFacing(UserFacing &&rhs) : handle(rhs.handle) { rhs.handle = nullptr; }
    UserFacing &operator=(UserFacing &&rhs) {
        if (handle) handle.destroy();
        handle = rhs.handle;
        rhs.handle = nullptr;
        return *this;
    }
    ~UserFacing() { handle.destroy(); }

    friend class SuspendOtherAwaiter;  // so it can get the handle
};

class TrivialAwaiter {
public:
    /**
     * controls whether the coroutine gets suspended at all.
     * If true, the coroutine just continues running.
     * If it returns false, the coroutine is suspended.
     */
    bool await_ready() { return false; }
    /**
     * If await_ready() returns false, then await_suspend() is called.
     * It can return void, in which case the coroutine is suspended and control is returned to whoever last resumed it.
     * It can return bool, in which case the coroutine is only suspended if the return value is true.
     * It can return a handle to another coroutine. In this case, the coroutine is suspended, the coroutine whose handle
     * you returned will resume running.
     */
    void await_suspend(std::coroutine_handle<>) {}
    void await_resume() {}
};

class ReadyTrueAwaiter {
public:
    bool await_ready() { return true; }
    void await_suspend(std::coroutine_handle<>) {}
    void await_resume() {}
};

class SuspendFalseAwaiter {
public:
    bool await_ready() { return false; }
    bool await_suspend(std::coroutine_handle<>) { return false; }
    void await_resume() {}
};

class SuspendTrueAwaiter {
public:
    bool await_ready() { return false; }
    bool await_suspend(std::coroutine_handle<>) { return true; }
    void await_resume() {}
};

class SuspendSelfAwaiter {
public:
    bool await_ready() { return false; }
    std::coroutine_handle<> await_suspend(std::coroutine_handle<> h) { return h; }
    void await_resume() {}
};

class SuspendNoopAwaiter {
public:
    bool await_ready() { return false; }
    std::coroutine_handle<> await_suspend(std::coroutine_handle<>) {
        // a ‘no-op coroutine’ don’t resume anything else, just return to the caller
        return std::noop_coroutine();
    }
    void await_resume() {}
};

class SuspendOtherAwaiter {
    std::coroutine_handle<> handle;

public:
    SuspendOtherAwaiter(UserFacing &uf) : handle(uf.handle) {}
    bool await_ready() { return false; }
    std::coroutine_handle<> await_suspend(std::coroutine_handle<>) { return handle; }
    void await_resume() {}
};

UserFacing demo_coroutine(UserFacing &aux_instance) {
    std::cout << "TrivialAwaiter:" << std::endl;
    co_await TrivialAwaiter{};  // to caller
    std::cout << "ReadyTrueAwaiter:" << std::endl;
    co_await ReadyTrueAwaiter{};  // coroutine continue to run
    std::cout << "SuspendFalseAwaiter:" << std::endl;
    co_await SuspendFalseAwaiter{};  // coroutine continue to run
    std::cout << "SuspendTrueAwaiter:" << std::endl;
    co_await SuspendTrueAwaiter{};  // coroutine suspend, return to caller
    std::cout << "SuspendSelfAwaiter:" << std::endl;
    co_await SuspendSelfAwaiter{};  // coroutine give control to itself, so it continue to run
    std::cout << "SuspendNoopAwaiter:" << std::endl;
    co_await SuspendNoopAwaiter{};  // to caller
    std::cout << "SuspendOtherAwaiter:" << std::endl;
    co_await SuspendOtherAwaiter{aux_instance};  // to another coroutine aux_instance
    std::cout << "goodbye from coroutine" << std::endl;
}

UserFacing aux_coroutine() {
    while (true) {
        std::cout << "  aux_coroutine was resumed" << std::endl;
        co_await std::suspend_always{};
    }
}

int main() {
    UserFacing aux_instance = aux_coroutine();
    UserFacing demo_instance = demo_coroutine(aux_instance);
    while (demo_instance.resume()) std::cout << "  suspended and came back to main()" << std::endl;
    std::cout << "and it's goodbye from main()" << std::endl;
}