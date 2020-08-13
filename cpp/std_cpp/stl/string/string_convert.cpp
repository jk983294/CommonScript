#include <cstdlib>
#include <iostream>

int main() {
    const char* buffer = "42";
    int i = std::stoi(buffer);
    long int li = std::stol(buffer);
    float fi = std::stof(buffer);
    double di = std::stod(buffer);
    unsigned long ul = std::stoul(buffer);
    std::cout << std::to_string(i) << '\n'
              << std::to_string(li) << '\n'
              << std::to_string(fi) << '\n'
              << std::to_string(di) << '\n'
              << std::to_string(ul) << '\n';

    // convert with specified base
    char szNumbers[] = "2001 60c0c0 -1101110100110100100000 0x6fffff";
    char* pEnd;
    long int li1, li2, li3, li4;
    li1 = std::strtol(szNumbers, &pEnd, 10);
    li2 = std::strtol(pEnd, &pEnd, 16);
    li3 = std::strtol(pEnd, &pEnd, 2);
    li4 = std::strtol(pEnd, nullptr, 0);
    std::cout << li1 << '\n' << li2 << '\n' << li3 << '\n' << li4 << '\n';
    return 0;
}
