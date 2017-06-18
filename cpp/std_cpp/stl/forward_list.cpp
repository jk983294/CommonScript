#include <forward_list>
#include <iostream>
#include <string>

using namespace std;

/**
 * singly-linked list, keeps internally only a pointer to the next element, not previous element pointer
 * it is the only standard container to deliberately lack a size member,
 * use the distance algorithm with its begin and end to get forward_list size
 */

int main() {
    std::forward_list<int> first;
    std::forward_list<int> second(3, 77);
    std::forward_list<int> third(second.begin(), second.end());
    std::forward_list<int> fourth(third);
    std::forward_list<int> fifth(std::move(fourth));  // move ctor. (fourth wasted)
    std::forward_list<int> sixth = {3, 52, 25, 90};

    std::cout << "first:";
    for (int& x : first) std::cout << " " << x;
    std::cout << '\n';

    std::cout << "second:";
    for (int& x : second) std::cout << " " << x;
    std::cout << '\n';

    std::cout << "third:";
    for (int& x : third) std::cout << " " << x;
    std::cout << '\n';

    std::cout << "fourth:";
    for (int& x : fourth) std::cout << " " << x;
    std::cout << '\n';

    std::cout << "fifth:";
    for (int& x : fifth) std::cout << " " << x;
    std::cout << '\n';

    std::cout << "sixth:";
    for (int& x : sixth) std::cout << " " << x;
    std::cout << '\n';
    return 0;
}
