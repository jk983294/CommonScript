#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim_all.hpp>
using namespace std;
using namespace boost;

bool is_executable(string&& filename)
{
    return iends_with(filename, ".exe");
}

bool is_all_lower(string&& text)
{
    return all(text, is_lower());
}

void split_demo()
{
    string str1("hello abc-*-ABC-*-aBc goodbye");

    typedef vector< string > split_vector_type;
    split_vector_type SplitVec;
    split(SplitVec, str1, is_any_of("-*-"), token_compress_on);      // SplitVec == { "hello abc","ABC","aBc goodbye" }
    for (auto& s : SplitVec)
    {
        cout << s << endl;
    }
}

int main(int argc, char *argv[])
{
    cout << boolalpha;
    string test = "\nhello   world \r\n";
    trim(test);
    cout << "<" << test << ">" << endl;
    trim_all(test);
    cout << "<" << test << ">" << endl;
    to_upper(test);
    cout << "<" << test << ">" << endl;

    cout << is_executable("a.exe") << endl;
    cout << is_all_lower("abexe") << endl;

    split_demo();

    getchar();
    return 0;
}