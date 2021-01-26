#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Object {
    int PrimaryCondition;
    int SecondaryCondition;
};

bool CompareData(const Object& a, const Object& b) {
    if (a.PrimaryCondition < b.PrimaryCondition) return true;
    if (b.PrimaryCondition < a.PrimaryCondition) return false;

    // a=b for primary condition, go to secondary
    if (a.SecondaryCondition < b.SecondaryCondition) return true;
    if (b.SecondaryCondition < a.SecondaryCondition) return false;
    return false;
}

int main() {
    std::vector<Object> v = {{1, 2}, {5, 3}, {2, 7}, {1, 1}};
    std::sort(v.begin(), v.end(), CompareData);

    for (auto& i : v) {
        cout << i.PrimaryCondition << "," << i.SecondaryCondition << endl;
    }
}
