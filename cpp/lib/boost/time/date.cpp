#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>

using namespace std;
using namespace boost::gregorian;

void basic() {
    date d1 = from_string("2018-02-01");
    date d2(from_string("2015/1/1"));
    date d3 = from_undelimited_string("20011118");
    date d4(2010, 1, 1);

    cout << d3 << endl;  // 2001-Nov-18

    cout << day_clock::local_day() << endl;      // local time 2018-Feb-01
    cout << day_clock::universal_day() << endl;  // GMT 2018-Feb-01

    date::ymd_type ymd = d1.year_month_day();
    cout << d1.year() << " " << d1.month() << " " << d1.day() << endl;  // 2018 Feb 1
    cout << ymd.year << " " << ymd.month << " " << ymd.day << endl;     // 2018 Feb 1

    cout << d1.day_of_week() << endl;   // Thu
    cout << d1.day_of_year() << endl;   // 32
    cout << d1.end_of_month() << endl;  // 2018-Feb-28

    cout << date(2018, 1, 10).week_number() << endl;  // 2
    cout << date(2018, 2, 1).week_number() << endl;   // 5
}

void format() {
    date d(2017, 1, 23);

    cout << to_simple_string(d) << endl;        // 2017-Jan-23
    cout << to_iso_string(d) << endl;           // 20170123
    cout << to_iso_extended_string(d) << endl;  // 2017-01-23
    cout << d << endl;                          // 2017-Jan-23
}

void convert_from_to_tm() {
    date d1(2017, 5, 20);
    tm t = to_tm(d1);
    date d2 = date_from_tm(t);
    cout << d2 << endl;  // 2017-May-20
}

void iterator_through() {
    date d(2018, 2, 3);
    date start(d.year(), d.month(), 1);
    date end = d.end_of_month();

    for (day_iterator itr = start; itr <= end; ++itr) {
        cout << *itr << " " << itr->day_of_week() << endl;
    }
}

int main() {
    basic();
    format();
    convert_from_to_tm();
    iterator_through();
    return 0;
}
