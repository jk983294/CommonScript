#include <cstdlib>
#include <iostream>

int main() {
    const char* buffer = "42";
    int i = std::atoi(buffer);
    long int li = std::atol(buffer);
    double di = std::atof(buffer);
    double di1 = std::strtod(buffer, NULL);
    unsigned long ul = std::strtoul(buffer, NULL, 0);
    std::cout << std::to_string(i) << '\n'
              << std::to_string(li) << '\n'
              << std::to_string(di) << '\n'
              << std::to_string(di1) << '\n'
              << std::to_string(ul) << '\n';

    // convert with specified base
    char szNumbers[] = "2001 60c0c0 -1101110100110100100000 0x6fffff";
    char* pEnd;
    long int li1, li2, li3, li4;
    li1 = std::strtol(szNumbers, &pEnd, 10);
    li2 = std::strtol(pEnd, &pEnd, 16);
    li3 = std::strtol(pEnd, &pEnd, 2);
    li4 = std::strtol(pEnd, NULL, 0);
    std::cout << li1 << '\n' << li2 << '\n' << li3 << '\n' << li4 << '\n';
    return 0;
}
