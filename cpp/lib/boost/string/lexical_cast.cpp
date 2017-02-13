#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
using namespace std;
using namespace boost;

int main(int argc, char *argv[])
{
    string s = "2.1";
    double d = lexical_cast<double>(s);
    cout << d << endl;

    string ss = "12345";
    int n = lexical_cast<int>(ss);
    cout << d << endl;

    try {
        lexical_cast<int>("abc");
    }
    catch (const bad_lexical_cast& e)
    {
        cout << e.what() << endl;
    }

    getchar();
    return 0;
}