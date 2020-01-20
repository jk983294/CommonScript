#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

struct Widget {
    int i{0};
    std::string s{};
    int* pi{nullptr};

    Widget() = default;
    Widget(Widget&& w) noexcept
        : i(std::move(w.i)), s(std::move(w.s)), pi(std::move(w.pi)) {  // phase1: member wise move
        w.pi = nullptr;                                                // phase2: reset
    }

    Widget& operator=(Widget&& w) noexcept {
        delete pi;           // destory resource you own
        i = std::move(w.i);  // grab other's resource
        s = std::move(w.s);
        pi = std::move(w.pi);
        w.pi = nullptr;  // clean up other's resource ownship
        return *this;
    }
};

struct Widget1 {
    int i{0};
    std::string s{};
    std::unique_ptr<int> pi;

    Widget1() = default;
    Widget1(Widget1&& w) = default;
    Widget1& operator=(Widget1&& w) = default;
};

int main() {
    Widget w;
    Widget1 w1;
    return 0;
}
