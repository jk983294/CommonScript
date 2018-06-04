#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

struct Object {
    int n;
    std::string s;
    float d;

    bool operator<(const Object& rhs) const {
        // compares n to rhs.n, then s to rhs.s, then d to rhs.d
        return std::tie(n, s, d) < std::tie(rhs.n, rhs.s, rhs.d);
    }
};

int main() {
    tuple<string, unsigned int, double> a;
    a = make_tuple("zz", 24, 60.0);
    get<1>(a) += 1;

    typedef tuple<string, unsigned int, double> Human;

    Human Yic("zz", 24, 60.0);
    vector<Human> vecHuman;
    vecHuman.push_back(a);
    vecHuman.push_back(Yic);

    cout << "name: " << get<0>(a) << endl;
    cout << "age: " << get<1>(a) << endl;
    cout << "weight: " << get<2>(a) << endl;

    std::set<Object> objects;  // S is LessThanComparable

    Object value{42, "Test", 3.14};
    std::set<Object>::iterator iter;
    bool inserted;

    // unpacks the return value of insert into iter and inserted
    std::tie(iter, inserted) = objects.insert(value);

    if (inserted) std::cout << "Value was inserted successfully\n";
    return 0;
}
