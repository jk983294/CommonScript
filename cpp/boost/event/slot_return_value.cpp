#include <iostream>
#include <string>
#include <vector>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>

using namespace std;
using namespace boost;
using namespace boost::signals2;

template <typename T> struct average
{
    typedef T result_type;

    template <typename II> T operator()(II first, II last)
    {
        if (first == last) return T();
        float sum = 0.0;
        int count = 0;
        while (first != last)
        {
            sum += *first++;
            count++;
        }
        return sum / count;
    }
};


int main(int argc, char *argv[])
{
    signal<float(float, float)> s;

    s.connect([](float a, float b){ return a + b; });
    s.connect([](float a, float b){ return a * b; });

    // return value is the last slot return value pointer
    cout << *s(3, 4) << endl;

    signal<float(float, float), average<float>> s1;

    s1.connect([](float a, float b){ return a + b; });
    s1.connect([](float a, float b){ return a * b; });

    // return value of the aggregator
    cout << s1(3, 4) << endl;

    getchar();
    return 0;
}