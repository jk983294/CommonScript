#include <iostream>
#include <map>

using namespace std;

template<typename T, typename U>
inline std::ostream& operator << (std::ostream& os, const map<T, U>& m)
{
    for (auto l_it = m.begin( ) ; l_it != m.end() ; ++l_it)    // sort by key
        os << l_it->first << " -> "<< l_it->second << endl;
    return os;
}
template<typename T, typename U, typename K>
inline std::ostream& operator << (std::ostream& os, const map<T, U, K>& m)
{
    for (auto l_it = m.begin( ) ; l_it != m.end() ; ++l_it)    // sort by key
        os << l_it->first << " -> "<< l_it->second << endl;
    return os;
}

bool fncomp(char lhs,char rhs)
{
    return lhs > rhs;
}
struct classcomp
{
    bool operator()(const char& lhs,const char& rhs)
    {
        return lhs > rhs;
    }
};

void user_defined_comparator(){
    map<char, int, classcomp> fourth;
    bool (*fn_pt)(char, char) = fncomp;
    map<char, int, bool(*)(char,char)> fifth(fn_pt);

    fourth['a']=10;
    fourth['b']=60;
    fourth['c']=30;
    fourth['d']=90;
    fourth['e']=50;
    cout << fourth << endl;

    fifth['a']=10;
    fifth['b']=60;
    fifth['c']=30;
    fifth['d']=90;
    fifth['e']=50;
    cout << fifth << endl;
}

int main()
{
    cout<<boolalpha;
    map<int, string> m, m1;
    map<int ,string >::iterator l_it;
    m.insert(pair<int, string>(1, "a"));
    m.insert(map<int, string>::value_type(2, "b"));
    m.insert(make_pair(7, "k"));
    m[9]="c";
    m[4]="d";
    m[-1]="k";

    cout << m.size() << endl;
    cout << m.empty() << endl;
    cout << m[4] << endl;
    cout << m << endl;

    // query
    l_it = m.find(9);
    if(l_it != m.end())
        cout << "wo find 9" << endl;
    if( m.count(9) > 0)
        cout << "wo find 9" << endl;

    // delete
    m.erase(9);

    if(m.find(9) == m.end())
        cout<<"we do not find 9"<<endl;

    // swap
    m1.swap(m);
    cout << m1 << endl;

    user_defined_comparator();

    return 0;
}