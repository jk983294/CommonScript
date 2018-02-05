#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>

using namespace std;
using namespace boost::gregorian;

void basic() {
    /**
     * [begin, end)
     */
    date_period dp1(date(2017, 1, 1), days(20));
    date_period dp2(date(2017, 2, 1), date(2016, 2, 11));
    date_period dp3(date(2017, 3, 1), days(-20));

    cout << dp1.is_null() << endl;        // false
    cout << dp1.begin().day() << endl;    // 1
    cout << dp1.last().day() << endl;     // 20
    cout << dp1.end().day() << endl;      // 21
    cout << dp1.length().days() << endl;  // 20

    if (dp1 < dp2) {          // compare begin point
        cout << dp1 << endl;  // [2017-Jan-01/2017-Jan-20]
    }
}

void shift_expand() {
    date_period dp(date(2017, 1, 1), days(20));

    dp.shift(days(3));                   // [begin + 3, end + 3)
    cout << dp.begin().day() << endl;    // 4
    cout << dp.length().days() << endl;  // 20

    dp.expand(days(3));                  // [begin - 3, end + 3)
    cout << dp.begin().day() << endl;    // 1
    cout << dp.length().days() << endl;  // 26
}

void arithmetic() {
    date_period dp1(date(2010, 1, 1), days(20));
    date_period dp2(date(2010, 1, 5), days(10));
    date_period dp3(date(2010, 1, 21), days(5));

    cout << dp1.is_after(date(2009, 12, 1)) << endl;  // true
    cout << dp1.is_before(date(2010, 2, 1)) << endl;  // true
    cout << dp1.contains(dp2) << endl;                // true
    cout << dp1.intersects(dp2) << endl;              // true
    cout << dp1.intersection(dp2) << endl;            // [2010-Jan-05/2010-Jan-14]
    cout << dp3.intersects(dp2) << endl;              // false
    cout << dp3.intersection(dp2).is_null() << endl;  // true
    cout << dp1.is_adjacent(dp3) << endl;             // true
}

void merge_span() {
    date_period dp1(date(2010, 1, 1), days(20));
    date_period dp2(date(2010, 1, 5), days(10));
    date_period dp3(date(2010, 2, 1), days(5));
    date_period dp4(date(2010, 1, 15), days(10));

    cout << dp1.merge(dp2) << endl;            // [2010-Jan-01/2010-Jan-20]
    cout << dp1.merge(dp3).is_null() << endl;  // true
    cout << dp1.merge(dp4) << endl;            // [2010-Jan-01/2010-Jan-24]
    cout << dp1.span(dp3) << endl;             // [2010-Jan-01/2010-Feb-05]
}

int main() {
    basic();
    shift_expand();
    arithmetic();
    merge_span();
    return 0;
}
