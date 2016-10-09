#include <iostream>

using namespace std;

int x = 10;

class Scope {
public:
    Scope(): x(0) {}
    void display(){
        int x = 3;
        cout << x << endl;                      // local
        cout << Scope::x << endl;               // object
        cout << this->x << endl;                // object
        cout << ::x << endl;                    // file
    }
private:
    int x;
};

int main() {
    int x = 13;
    cout << x << endl;                          // local
    cout << ::x << endl;                        // file
    Scope scope;
    scope.display();
    return 0;
}