#include <iostream>
#include <memory>
#include <string>

using namespace std;

/**
 * private data members participate in class layout and private member functions participate in overload resolution,
 * changes to those implementation details require recompilation of all users of a class that uses them.
 * A non-polymorphic interface class holding a pointer to implementation (Pimpl) can isolate the users of a class
 * from changes in its implementation at the cost of an indirection
 */

class widget;

class impl {
private:
    int n;

public:
    void draw() { cout << n << endl; }
    impl(int n) : n(n) {}
};

class widget {
    std::shared_ptr<impl> pimpl;

public:
    void draw() { pimpl->draw(); }  // public API that will be forwarded to the implementation
    widget(int n) : pimpl{std::make_shared<impl>(n)} {}
    ~widget() = default;
    widget(widget&&) = default;
    widget(const widget&) = delete;
    widget& operator=(widget&&) = default;
    widget& operator=(const widget&) = delete;
};

int main(int argc, char const* argv[]) {
    std::shared_ptr<widget> w = std::make_shared<widget>(42);
    w->draw();
    return 0;
}
