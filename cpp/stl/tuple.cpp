#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

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
    cout<<"age: "<<get<1>(a)<<endl;
    cout<<"weight: "<<get<2>(a)<<endl;
    return 0;
}