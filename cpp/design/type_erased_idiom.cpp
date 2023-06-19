#include <iostream>
#include <memory>
#include <vector>

struct Circle {
    explicit Circle(double rad) : radius{rad} {}
    double radius;
};

struct Square {
    explicit Square(double s) : side{s} {}
    double side;
};

struct Rectangle {
    explicit Rectangle(double s1, double s2) : side1{s1}, side2{s2} {}
    double side1, side2;
};

// Wrapper over the external polymorphism pattern
class Shape {
private:
    struct ShapeConcept {
        virtual ~ShapeConcept() = default;

        virtual void do_draw() const = 0;

        // Usage of the prototype design pattern to allow copy
        [[nodiscard]] virtual std::unique_ptr<ShapeConcept> clone() const = 0;
    };

    template <typename GeomShape>
    struct ShapeModel : ShapeConcept {
        ShapeModel(GeomShape shape) : shape_{std::move(shape)} {}

        void do_draw() const override { draw(shape_); }

        // Usage of the prototype design pattern to allow copy
        [[nodiscard]] std::unique_ptr<ShapeConcept> clone() const override {
            // Note the use of the copy constructor of the ShapeModel.
            // This will always do the right thing. even if other code changes.
            return std::make_unique<ShapeModel>(*this);
        }

        GeomShape shape_;
    };

    // Free function and injected into the surrounding namespace
    // Not part of the class
    // This friend fct trigger the polymorphic behavior
    // It goes to the pimpl and call the do_draw fct.
    // Doing so, trigger the "real" polymorphic behavior
    friend void draw(Shape const& shape) { shape.pimpl->do_draw(); }

    std::unique_ptr<ShapeConcept> pimpl;  // Used for the bridge design pattern

public:
    // Template constructor that take any type of shape and deduce the type
    // This is creating a bridge to some implementation details that the compiler generate
    template <typename GeomShape>
    Shape(GeomShape shape) : pimpl{std::make_unique<ShapeModel<GeomShape>>(std::move(shape))} {}

    // Special member functions;
    Shape(Shape const& s) : pimpl(s.pimpl->clone()) {}

    Shape& operator=(Shape const& s) {
        // Copy-and-swap idiom
        s.pimpl->clone().swap(pimpl);
        return *this;
    }

    // Default are ok due to the unique_ptr
    // Move will leave an empty shape, remember
    Shape(Shape&& s) = default;
    Shape& operator=(Shape&& s) = default;
};

void draw(Circle const& c) { std::cout << "Circle radius: " << c.radius << std::endl; }

void draw(Square const& s) { std::cout << "Square side: " << s.side << std::endl; }

void draw(Rectangle const& s) { std::cout << "Rectangle " << s.side1 << ":" << s.side2 << std::endl; }

/**
 * Here you should enjoy the output of the Type-Erased pattern:
 *  1 - No pointers for the user
 *  2 - No manual dynamic allocation
 *  3 - No manual life-time management
 *  4 - Value semantics used
 *  5 - Very simple code ( KISS )
 */
int main() {
    std::vector<Shape> shapes;

    shapes.emplace_back(Circle{2.0});
    shapes.emplace_back(Square(5));
    shapes.emplace_back(Circle{4});
    shapes.emplace_back(Square(10));
    shapes.emplace_back(Rectangle(10, 15));

    for (auto const& shape : shapes) {
        draw(shape);
    }
    return 0;
}