#include <iostream>

using namespace std;

/**
 * prefer class enums over “plain” enums
 */

enum Choice { No, Yes };
enum Lights { RED, YELLOW, AMBER = YELLOW, GREEN };
enum { BUF_SIZE = 1024 };
// #include BUF_SIZE 1024

int main() {
    cout << boolalpha;
    cout << No << " " << Yes << endl;
    cout << Lights::RED << " " << Lights::YELLOW << " " << Lights::AMBER << " " << Lights::GREEN << endl;
    cout << BUF_SIZE << endl;

    // enum int cast between each other
    Lights l = Lights::RED;
    int lightIndex = Lights::RED;
    l = Lights(lightIndex);
    return 0;
}
