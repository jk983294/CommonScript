#include <iostream>
#include <memory>
#include <variant>
#include <vector>

/**
 * g++ -std=c++17 crtp_version.cpp
 */

template <typename TDerived>
struct Shape {
    void draw() const { derived()->drawImpl(); }
    const TDerived* derived() const { return static_cast<const TDerived*>(this); }
};

struct Circle : public Shape<Circle> {
    void drawImpl() const { std::cout << "Drawing a Circle\n"; }
};

struct Square : public Shape<Square> {
    void drawImpl() const { std::cout << "Drawing a Square\n"; }
};

struct Triangle : public Shape<Triangle> {
    void drawImpl() const { std::cout << "Drawing a Triangle\n"; }
};

using TVar = std::variant<Circle*, Square*, Triangle*>;

int main() {
    Circle c;
    Square s;
    Triangle t;
    std::vector<TVar> shapes{&c, &s, &t};
    /**
     * don't do below, because no way to delete those new objects, type info has lost
     */
    // shapes.push_back(new Circle);
    // shapes.push_back(new Square);
    // shapes.push_back(new Triangle);

    for (auto& s : shapes) {
        std::visit([](auto* v) { v->draw(); }, s);
    }
    return 0;
}