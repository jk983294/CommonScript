#include <boost/container/flat_map.hpp>
#include <iostream>

using namespace std;

template <typename T, typename U>
inline std::ostream& operator<<(std::ostream& os, const boost::container::flat_map<T, U>& m) {
    for (auto l_it = m.begin(); l_it != m.end(); ++l_it)  // sort by key
        os << l_it->first << " -> " << l_it->second << endl;
    return os;
}
template <typename T, typename U, typename K>
inline std::ostream& operator<<(std::ostream& os, const boost::container::flat_map<T, U, K>& m) {
    for (auto l_it = m.begin(); l_it != m.end(); ++l_it)  // sort by key
        os << l_it->first << " -> " << l_it->second << endl;
    return os;
}

int main() {
    cout << boolalpha;
    boost::container::flat_map<int, string> m, m1;
    boost::container::flat_map<int, string>::iterator l_it;
    m.insert(pair<int, string>(1, "a"));
    m.insert(boost::container::flat_map<int, string>::value_type(2, "b"));
    m.insert(pair<int, string>(7, "k"));
    m[9] = "c";
    m[4] = "d";
    m[-1] = "k";

    cout << m.size() << endl;
    cout << m.empty() << endl;
    cout << m[4] << endl;
    cout << m << endl;

    // query
    l_it = m.find(9);
    if (l_it != m.end()) cout << "we find 9" << endl;
    if (m.count(9) > 0) cout << "we find 9" << endl;

    // delete
    m.erase(9);

    if (m.find(9) == m.end()) cout << "we do not find 9" << endl;

    // swap
    m1.swap(m);
    cout << m1 << endl;

    boost::container::flat_map<char, int> fourth;
    fourth['a'] = 10;
    fourth['b'] = 60;
    fourth['c'] = 30;
    fourth['d'] = 90;
    fourth['e'] = 50;
    cout << fourth << endl;
    return 0;
}
