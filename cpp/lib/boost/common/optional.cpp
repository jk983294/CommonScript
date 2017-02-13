#include <iostream>
#include <string>
#include <boost/optional.hpp>

using namespace std;
using namespace boost;

class Address
{
public:
    Address(string streetName) : streetName(streetName) {}
    string streetName;
};

class Person
{
public:
    Person(string firstName, string lastName) :
        firstName(firstName), lastName(lastName) {}

    string firstName, lastName;
    optional<string> middleName;
    optional<Address> address;
};

int main()
{
    Person p{ "a", "b" };
    p.middleName = "c";
    p.address = Address{ "d" };

    if (p.middleName)
        cout << *p.middleName << endl;

    if (p.address)
        cout << p.address->streetName << endl;

    return 0;
}