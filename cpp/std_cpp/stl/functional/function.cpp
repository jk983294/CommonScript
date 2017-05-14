#include <functional>
#include <iostream>

struct Foo {
    Foo(int num) : num_(num) {}
    void print_add(int i) const { std::cout << num_ + i << '\n'; }
    int num_;
};

void print_num(int i) { std::cout << i << '\n'; }

struct PrintNum {
    void operator()(int i) const { std::cout << i << '\n'; }
};

int main() {
    // free function
    std::function<void(int)> f_display = print_num;
    f_display(-9);

    // lambda
    std::function<void()> f_display_42 = []() { print_num(42); };
    f_display_42();

    // member function
    std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
    const Foo foo(314159);
    f_add_display(foo, 1);

    // data member accessor
    std::function<int(Foo const&)> f_num = &Foo::num_;
    std::cout << "num_: " << f_num(foo) << '\n';
    return 0;
}
