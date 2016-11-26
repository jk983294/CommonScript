#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim_all.hpp>
using namespace std;
using namespace boost;

int main(int argc, char *argv[])
{
    string test = "\nhello   world \r\n";
    trim(test);
    cout << "<" << test << ">" << endl;
    trim_all(test);
    cout << "<" << test << ">" << endl;
    to_upper(test);
    cout << "<" << test << ">" << endl;

    getchar();
    return 0;
}