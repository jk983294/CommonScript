#include <iostream>
#include <variant>
#include <vector>

/**
 * g++ -std=c++17 variant_version.cpp
 */

struct Circle {
    void draw() const { std::cout << "Drawing a Circle\n"; }
};

struct Square {
    void draw() const { std::cout << "Drawing a Square\n"; }
};

struct Triangle {
    void draw() const { std::cout << "Drawing a Triangle\n"; }
};

using Shape = std::variant<Circle, Square, Triangle>;

struct DrawVisitor {
    void operator()(const Circle& circle) const { circle.draw(); }
    void operator()(const Square& square) const { square.draw(); }
    void operator()(const Triangle& triangle) const { triangle.draw(); }
};

int main() {
    std::vector<Shape> shapes = {Circle{}, Square{}, Triangle{}};

    for (const auto& shape : shapes) {
        std::visit(DrawVisitor{}, shape);
    }
    return 0;
}