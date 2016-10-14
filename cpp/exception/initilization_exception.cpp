#include <iostream>
#include <string>
#include <exception>

using namespace std;

class Employee
{
    double wage;
    string name;
public:
    Employee(const double wage_, const string& s)
            try : wage(wage_), name(s)
    {
    }
    catch (...) {
        cout << "initialization exception" << endl;
    }
};

int main(){
    Employee e(1.0, "kun");
    return 0;
}