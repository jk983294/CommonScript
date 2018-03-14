#include <functional>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

template <typename Event>
class Subject {
public:
    Subject() = default;
    Subject(const Subject &) = delete;
    Subject &operator=(const Subject &) = delete;

    template <typename Observer>
    void register_observer(const Event &event, Observer &&observer) {
        observers[event].push_back(std::forward<Observer>(observer));
    }

    template <typename Observer>
    void register_observer(Event &&event, Observer &&observer) {
        observers[std::move(event)].push_back(std::forward<Observer>(observer));
    }

    void notify(const Event &event) const {
        for (const auto &obs : observers.at(event)) obs();
    }

private:
    std::map<Event, std::vector<std::function<void()>>> observers;
};

void foo(int i) { std::cout << "foo( " << i << " )\n"; }

void bar() { std::cout << "bar()\n"; }

class MyObject {
public:
    void meow() { std::cout << "MyObject::meow() with data " << data << "\n"; }

public:
    int data{42};
};

int main() {
    Subject<std::string> s;
    s.register_observer("GREEN", bar);
    s.register_observer("ORANGE", std::bind(foo, 24));
    s.register_observer("RED", std::bind(foo, 12345));
    const std::string msg("Hello, RED!");
    s.register_observer("RED", [&msg] { std::cout << msg << std::endl; });
    MyObject myObject;
    s.register_observer("BLUE", std::bind(&MyObject::meow, &myObject));

    s.notify("GREEN");
    s.notify("RED");
    s.notify("ORANGE");
    s.notify("BLUE");
    return 0;
}
