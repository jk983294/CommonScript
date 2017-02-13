#include <iostream>

using namespace std;

enum Choice { No, Yes };
enum Lights { RED, YELLOW, AMBER = YELLOW, GREEN };
enum { BUF_SIZE = 1024 };
// #include BUF_SIZE 1024


int main() {
    cout<<boolalpha;
    cout << No << " " << Yes << endl;
    cout << RED << " " << YELLOW << " " << AMBER << " " << GREEN << endl;
    cout << BUF_SIZE << endl;

    // enum int cast between each other
    Lights l = RED;
    int lightIndex = RED;
    l = Lights(lightIndex);
    return 0;
}