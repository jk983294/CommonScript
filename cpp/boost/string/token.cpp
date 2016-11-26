#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
using namespace std;
using namespace boost;

int main(int argc, char *argv[])
{
    string s = "To be, or not to be?";
    tokenizer<> t(s);

    for (string part : t)
        cout << part << endl;

    cout << "=====================" << endl;
    char_separator<char> sep("\t", " ");
    string s1 = "1\t2\t3";
    tokenizer<char_separator<char>> t1(s1, sep);
    for (string part : t1)
        cout << part << endl;

    cout << "=====================" << endl;
    int offsets[] = { 2, 4, 7 };
    offset_separator os(offsets, offsets + 3);

    auto start = make_token_iterator<string>(s.begin(), s.end(), os);
    auto end = make_token_iterator<string>(s.end(), s.end(), os);

    for (; start != end; ++start)
        cout << *start << endl;

    getchar();
    return 0;
}