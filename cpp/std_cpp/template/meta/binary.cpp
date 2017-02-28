#include <iostream>

using namespace std;

template <unsigned long N>
struct binary
{
    static unsigned const value = binary<N/10>::value * 2 + N % 10;
};

template <>
struct binary<0>
{
    static unsigned const value = 0;
};

int main(){
    cout << binary<10010>::value << endl;
    cout << binary<1>::value << endl;
    cout << binary<0>::value << endl;
    return 0;
}
