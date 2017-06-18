#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// the argument is a class template

template <typename T, typename U>
std::ostream& operator<<(std::ostream& out, const std::pair<T, U>& p) {
    out << "[" << p.first << ", " << p.second << "]";
    return out;
}
template <template <typename, typename> class ContainerType, typename ValueType, typename AllocType>
void print_container(const ContainerType<ValueType, AllocType>& c) {
    for (const auto& v : c) cout << v << ' ';
    cout << endl;
}

template <template <typename, typename...> class ContainerType, typename ValueType, typename... Args>
void print_container(const ContainerType<ValueType, Args...>& c) {
    for (const auto& v : c) cout << v << ' ';
    cout << endl;
}

int main() {
    print_container(vector<int>{1, 3, 5, 7, 9});
    print_container(map<int, int>{{1, 1}, {2, 2}});
    return 0;
}
