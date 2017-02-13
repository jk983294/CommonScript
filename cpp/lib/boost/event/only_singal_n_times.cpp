#include <iostream>
#include <string>
#include <ctime>
#include <boost/signals2.hpp>

using namespace std;
using namespace boost;
using namespace boost::signals2;

int main(int argc, char *argv[])
{
    signal<void(int)> values;

    values.connect_extended(
        [](const connection& conn, int value)
    {
        static int count = 0;
        if (++count > 5)
            conn.disconnect();
        else
            cout << "value is " << value << endl;
    });

    srand((unsigned)time(nullptr));
    for (size_t i = 0; i < 100; i++)
    {
        values(rand());
    }

    getchar();
    return 0;
}