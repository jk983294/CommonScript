#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
using namespace std;

/**
* explicit conversion operator
*/

class SmartPtr {
public:
    /*explicit*/ operator bool() const {	                // explicit prevent it from convert to int
        return true;
    }
};

class Example{
public:
    Example();
    Example(int val);
    operator unsigned int();
    ~Example(){}
private:
    int itsVal;
};

Example::Example():itsVal(0){}
Example::Example(int val):itsVal(val){}
Example::operator unsigned int (){
    cout << "conversion: " << itsVal << endl;
    return (itsVal);
}

int main() {
    SmartPtr p;
    bool b(p);
    // cout << p * 123 << endl;			                    // explicit prevent it from convert to int
    if(p){
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }

    int theInt = 8;
    Example exObject = theInt;
    Example ctr(5);
    int theInt1 = ctr;
    return 0;
}