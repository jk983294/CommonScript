#include <iostream>
#include <string>
#include <vector>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>

using namespace std;
using namespace boost;
using namespace boost::signals2;

int main(int argc, char *argv[])
{
    signal<void()> s;

    {
        auto c = s.connect(1, [](){ cout << "first." << endl; });
        scoped_connection sc(c);    // this slot only be signaled in this scope

        s.connect(0, [](){ cout << "second." << endl; });

        s();
    }

    s();

    getchar();
    return 0;
}