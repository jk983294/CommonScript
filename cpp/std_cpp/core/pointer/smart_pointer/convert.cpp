#include <iostream>
#include <memory>

struct Base {
    int a;
    virtual void f() const { std::cout << "I am base!\n"; }
    virtual ~Base() = default;
};

struct Derived : Base {
    void f() const override { std::cout << "I am derived!\n"; }
    ~Derived() override {}
};

int main() {
    auto basePtr = std::make_shared<Base>();
    std::cout << "Base pointer says: ";
    basePtr->f();

    auto derivedPtr = std::make_shared<Derived>();
    std::cout << "Derived pointer says: ";
    derivedPtr->f();

    // static_pointer_cast to go up class hierarchy
    basePtr = std::static_pointer_cast<Base>(derivedPtr);
    std::cout << "Base pointer to derived says: ";
    basePtr->f();

    // dynamic_pointer_cast to go down/across class hierarchy
    auto downcastedPtr = std::dynamic_pointer_cast<Derived>(basePtr);
    if (downcastedPtr) {
        std::cout << "Downcasted pointer says: ";
        downcastedPtr->f();
    }

    // All pointers to derived share ownership
    std::cout << "Pointers to underlying derived: " << derivedPtr.use_count() << "\n";
}