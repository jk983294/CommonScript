#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

struct Foo {
    void display_greeting() { std::cout << "Hello, world.\n"; }
    void display_number(int i) { std::cout << "number: " << i << '\n'; }
    int data = 7;
};
class Shape {
public:
    virtual void display() = 0;
};
class Circle : public Shape {
public:
    virtual void display() { std::cout << "circle" << '\n'; }
};
class Rect : public Shape {
public:
    virtual void display() { std::cout << "rect" << '\n'; }
};

int main() {
    Foo f;

    auto greet = std::mem_fn(&Foo::display_greeting);
    greet(f);

    auto print_num = std::mem_fn(&Foo::display_number);
    print_num(f, 42);

    auto access_data = std::mem_fn(&Foo::data);
    std::cout << "data: " << access_data(f) << '\n';

    // polymorphism
    std::vector<Shape*> v;
    v.push_back(new Circle);
    v.push_back(new Rect);
    for_each(v.begin(), v.end(), std::mem_fn(&Shape::display));
    return 0;
}
