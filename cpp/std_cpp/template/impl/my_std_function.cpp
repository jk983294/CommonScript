#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>

template <typename Fun>
class MyFunction;

template <typename Ret, typename... Args>
class MyFunction<Ret(Args...)> {
private:
    class function_control_block_base {
        friend class MyFunction;

    private:
        virtual function_control_block_base* clone() const = 0;
        virtual Ret invoke(Args... args) const = 0;
        virtual ~function_control_block_base() = default;
    };

    template <typename Fun>
    class function_control_block : function_control_block_base {
        friend class MyFunction;

    private:
        Fun fun;

        function_control_block(const function_control_block&) = default;

        explicit function_control_block(Fun&& fun) : fun(std::forward<Fun>(fun)) {}

        virtual function_control_block_base* clone() const { return new function_control_block(*this); }

        virtual Ret invoke(Args... args) const { return fun(std::forward<Args>(args)...); }
    };

    function_control_block_base* control_block{nullptr};

public:
    MyFunction() = default;

    MyFunction(const MyFunction& src) : control_block(src.control_block->clone()) {}

    MyFunction(MyFunction&& src) : control_block(src.control_block) { src.control_block = nullptr; }

    template <typename Fun>
    MyFunction(Fun&& fun) : control_block(new function_control_block<Fun>(std::forward<Fun>(fun))) {}

    ~MyFunction() { delete control_block; }

    void swap(MyFunction& ano) { std::swap(this->control_block, ano.control_block); }

    explicit operator bool() const { return this->control_block != nullptr; }

    Ret operator()(Args... args) const {
        if (!static_cast<bool>(*this)) {
            throw std::bad_function_call();
        }
        return this->control_block->invoke(std::forward<Args>(args)...);
    }
};

int add(int x) { return x + 1; }

int add2(int x, int y) { return x + y; }

int main() {
    MyFunction<int(int)> f = add;
    std::cout << f(3) << std::endl;

    int out = 7;
    auto lam = [&out](int x) {
        out += x;
        return out;
    };
    MyFunction<int(int)> f2 = lam;

    std::cout << f2(3) << std::endl;
    std::cout << out << std::endl;

    MyFunction<int(int)> f3 = std::bind(add2, 7, std::placeholders::_1);
    std::cout << f3(7) << std::endl;
}