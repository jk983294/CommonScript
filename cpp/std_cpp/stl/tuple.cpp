#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    tuple<string, int> a;
    a = make_tuple("x", 24);
    get<1>(a) += 1;
    cout << "name: " << get<0>(a) << endl;
    cout << "age: " << get<1>(a) << endl;

    typedef tuple<string, int> Human;

    Human Yic("y", 24);
    vector<Human> vecHuman;
    vecHuman.push_back(a);
    vecHuman.push_back(Yic);

    auto tmp = std::tuple_cat(a, std::make_tuple("Foo", "bar"));
    cout << get<0>(tmp) << " " << get<1>(tmp) << " " << get<2>(tmp) << " " << get<3>(tmp) << endl;
    return 0;
}
