#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    char x = 'x';
    auto anyone = [](auto&& k, auto&&... args) ->bool { return ((args == k) || ...); };
    if(anyone(x,'x','X','e','E','.')){
        cout << "match\n";
    }
    return 0;
}