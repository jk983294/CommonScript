#include <string>
#include <iostream>
#include <memory>
using namespace std;

/**
 * Problem
 * decide at run time what object is to be created based on some configuration or application parameter.
 * Solution
 * Define an interface for creating an object, but let subclasses decide which class to instantiate.
 * Factory Method lets a class defer instantiation to subclasses.
 */

class Pizza {
public:
    virtual int getPrice() const = 0;
    virtual ~Pizza() {};
};

class HamAndMushroomPizza : public Pizza {
public:
    virtual int getPrice() const { return 850; };
    virtual ~HamAndMushroomPizza() {};
};

class DeluxePizza : public Pizza {
public:
    virtual int getPrice() const { return 1050; };
    virtual ~DeluxePizza() {};
};

class HawaiianPizza : public Pizza {
public:
    virtual int getPrice() const { return 1150; };
    virtual ~HawaiianPizza() {};
};

class PizzaFactory {
public:
    enum PizzaType {
        HamMushroom,
        Deluxe,
        Hawaiian
    };

    static unique_ptr<Pizza> createPizza(PizzaType pizzaType) {
        switch (pizzaType) {
            case HamMushroom: return unique_ptr<HamAndMushroomPizza>(new HamAndMushroomPizza());
            case Deluxe:      return unique_ptr<DeluxePizza>(new DeluxePizza());
            case Hawaiian:    return unique_ptr<HawaiianPizza>(new HawaiianPizza());
        }
        throw "invalid pizza type.";
    }
};


void pizza_information(PizzaFactory::PizzaType pizzaType)
{
    unique_ptr<Pizza> pizza = PizzaFactory::createPizza(pizzaType);
    cout << "Price of " << pizzaType << " is " << pizza->getPrice() << std::endl;
}

int main()
{
    pizza_information(PizzaFactory::HamMushroom);
    pizza_information(PizzaFactory::Deluxe);
    pizza_information(PizzaFactory::Hawaiian);
    return 0;
}