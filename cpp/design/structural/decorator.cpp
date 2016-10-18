#include <string>
#include <iostream>
#include <memory>

using namespace std;

/**
 * Problem
 * The decorator pattern helps to attach additional behavior or responsibilities to an object dynamically.
 * This is also called wrapper
 */

class Car
{
protected:
    string _str;
public:
    Car() {
        _str = "Unknown Car";
    }
    virtual string getDescription() {
        return _str;
    }
    virtual double getCost() = 0;
    virtual ~Car() {
        cout << "~Car()" << endl;
    }
};

class OptionsDecorator : public Car
{
public:
    virtual string getDescription() = 0;
    virtual ~OptionsDecorator() {
        cout<<"~OptionsDecorator()" << endl;
    }
};


class CarModel1 : public Car
{
public:
    CarModel1() {
        _str = "CarModel1";
    }
    virtual double getCost() {
        return 31000.23;
    }
    ~CarModel1() {
        cout<<"~CarModel1()" << endl;
    }
};

class Navigation: public OptionsDecorator
{
    Car *_b;
public:
    Navigation(Car *b) {
        _b = b;
    }
    string getDescription() {
        return _b->getDescription() + ", Navigation";
    }
    double getCost() {
        return 300.56 + _b->getCost();
    }
    ~Navigation() {
        cout << "~Navigation()" << endl;
    }
};
class PremiumSoundSystem: public OptionsDecorator
{
    Car *_b;
public:
    PremiumSoundSystem(Car *b) {
        _b = b;
    }
    string getDescription() {
        return _b->getDescription() + ", PremiumSoundSystem";
    }
    double getCost() {
        return 0.30 + _b->getCost();
    }
    ~PremiumSoundSystem() {
        cout << "~PremiumSoundSystem()" << endl;
    }
};
class ManualTransmission: public OptionsDecorator
{
    Car *_b;
public:
    ManualTransmission(Car *b) {
        _b = b;
    }
    string getDescription() {
        return _b->getDescription()+ ", ManualTransmission";
    }
    double getCost() {
        return 0.30 + _b->getCost();
    }
    ~ManualTransmission() {
        cout << "~ManualTransmission()" << endl;
    }
};

class CarDecoratorExample{
public:
    void execute() {
        //Create our Car that we want to buy
        Car *b = new CarModel1();

        cout << "Base model of " << b->getDescription() << " costs $" << b->getCost() << endl;

        //Who wants base model lets add some more features
        b = new Navigation(b);
        cout << b->getDescription() << " will cost you $" << b->getCost() << endl;
        b = new PremiumSoundSystem(b);
        b = new ManualTransmission(b);
        cout << b->getDescription() << " will cost you $" << b->getCost() << endl;

        // WARNING! Here we leak the CarModel1, Navigation and PremiumSoundSystem objects!
        // either we delete them explicitly or rewrite the Decorators to take ownership and delete their Cars when destroyed.
        delete b;
    }

};

int main()
{
    CarDecoratorExample b;
    b.execute();
    return 0;
}