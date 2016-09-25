#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
using namespace std;

/**
* virtual functions
*/

class Shape {
public:
    Shape(){};
    virtual ~Shape(){}
    virtual void draw(int x, int y){
        cout << "Shape::draw(" <<x << ", " << y << ")" << endl;
    }
    void f(int x, int y){
        cout << "not virtual!!! Shape::f(" <<x << ", " << y << ")" << endl;
        do_f(x, y);
        cout << "bye!" << endl;
    }
private:
    virtual void do_f(int x, int y){
        cout << "Shape::do_f(" <<x << ", " << y << ")" << endl;
    }
    Shape(const Shape&);
    Shape& operator=(const Shape&);
};

class Polygon : public Shape {
public:
    virtual void draw(int x, int y) override {
        cout << "Polygon::draw(" <<x << ", " << y << ")" << endl;
    }
private:
    virtual void do_f(int x, int y){
        cout << "Polygon::do_f(" <<x << ", " << y << ")" << endl;
    }
};

class Evilgon : public Shape {
public:
    // override will fail to compile, because no match virtual function found in base class
    virtual void draw(double x, double y){
        cout << "Evilgon::draw(" <<x << ", " << y << ")" << endl;
    }
private:
    virtual void do_f(int x, int y){
        cout << "Evilgon::do_f(" <<x << ", " << y << ")" << endl;
    }
};

// final prevent this class derived
class Triangle final : public Polygon {
public:
    // final prevent this function override
    virtual void draw(int x, int y) final override {
        cout << "Triangle::draw(" <<x << ", " << y << ")" << endl;
    }
};
/*
class BermudaTriangle : public Triangle {
public:
	virtual void draw(int x, int y) override {
		cout << "BermudaTriangle::draw(" <<x << ", " << y << ")" << endl;
	}
};
/**/

int main() {
    shared_ptr<Shape> p = make_shared<Polygon>();
    p->draw(11, 22);
    p->f(11, 22);

    p = make_shared<Evilgon>();
    p->draw(11.1, 22.2);							        // call base function because function signature not match
    return 0;
}