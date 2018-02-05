#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>

using namespace std;
using namespace boost::gregorian;

void duration() {
    days dd1(10), dd2(-100), dd3(255);

    assert(dd1 > dd2 && dd1 < dd3);
    assert(dd1 + dd2 == days(-90));
    assert((dd1 + dd3).days() == 265);
    assert(dd3 / 5 == days(51));

    weeks w(3);
    months m(5);
    years y(2);
    cout << w.days() << endl;              // 21
    cout << m.number_of_months() << endl;  // 5
    cout << y.number_of_years() << endl;   // 2

    months m2 = y + m;
    cout << m2.number_of_months() << endl;      // 29
    cout << (y * 2).number_of_years() << endl;  // 4
}

void arithmetic() {
    date d1(2000, 1, 1), d2(2017, 11, 18);
    cout << d2 - d1 << endl;

    d1 += days(10);
    cout << d1.day() << endl;  // 11
    d1 += months(2);
    cout << d1.month() << endl;  // 3
    d1 -= weeks(1);
    cout << d1.day() << endl;  // 4
    d2 -= years(10);
    cout << d2.year() << endl;  // 2007

    {
        date d(2017, 3, 30);
        d -= months(1);
        d -= months(1);
        d += months(2);
        assert(d.day() == 31);
    }
}

int main() {
    duration();
    arithmetic();
    return 0;
}
