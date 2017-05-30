#include <iostream>
#include <memory>

struct C : std::enable_shared_from_this<C> {};

int main() {
    std::shared_ptr<C> foo, bar;
    foo = std::make_shared<C>();
    bar = foo->shared_from_this();
    if (!foo.owner_before(bar) && !bar.owner_before(foo)) std::cout << "foo and bar share ownership";
    return 0;
}
