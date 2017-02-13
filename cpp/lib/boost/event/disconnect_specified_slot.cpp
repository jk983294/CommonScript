#include <iostream>
#include <string>
#include <vector>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>

using namespace std;
using namespace boost;
using namespace boost::signals2;

void third()
{
    cout << "third" << endl;
}

int main(int argc, char *argv[])
{
    signal<void()> s;
    s.connect(third);
    {
        auto c = s.connect(1, [](){ cout << "first.." << endl; });
        scoped_connection sc(c);
        s.connect(0, [](){ cout << "second.." << endl; });

        s();
    }
    cout << "=================" << endl;
    s.disconnect(third);
    s();

    getchar();
    return 0;
}