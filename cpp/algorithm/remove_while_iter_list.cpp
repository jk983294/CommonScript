#include <iostream>
#include <list>

using namespace std;

int main() {
    std::list<int> l = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto itr = l.begin();
    while (itr != l.end()) {
        if (*itr % 2 == 1) {  // remove odd number
            l.erase(itr++);
        } else {
            ++itr;
        }
    }

    itr = l.begin();
    while (itr != l.end()) {
        cout << *itr << " ";
        itr++;
    }
    cout << endl;
}