#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include "tbb/blocked_range.h"
#include "tbb/concurrent_hash_map.h"
#include "tbb/parallel_for.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/tbb_allocator.h"
#include "tbb/tick_count.h"

using namespace tbb;
using namespace std;

struct MyHashCompare {
    static size_t hash(const string& x) {
        size_t h = 0;
        for (const char* s = x.c_str(); *s; ++s) {
            h = (h * 17) ^ *s;
        }
        return h;
    }

    static bool equal(const string& x, const string& y) { return x == y; }
};

// concurrent hash table that maps strings to ints.
typedef concurrent_hash_map<string, int, MyHashCompare> StringTable;

// function object for counting occurrences of strings.
struct Tally {
    StringTable& table;
    Tally(StringTable& table_) : table(table_) {}
    void operator()(const blocked_range<string*> range) const {
        for (string* p = range.begin(); p != range.end(); ++p) {
            // accessor for write, const_accessor for read
            StringTable::accessor a;
            table.insert(a, *p);
            a->second += 1;
        }
    }
};

string generateRandomString() {
    char str[9];
    char c1 = rand() % 26 + 65;
    char c2 = rand() % 26 + 65;
    char c3 = rand() % 26 + 65;
    char c4 = rand() % 26 + 65;

    char c5 = rand() % 26 + 65;
    char c6 = rand() % 26 + 65;
    char c7 = rand() % 26 + 65;
    char c8 = rand() % 26 + 65;

    sprintf(str, "%c%c%c%c%c%c%c%c", c1, c2, c3, c4, c5, c6, c7, c8);
    return string(str);
}

int main(int argc, char* argv[]) {
    tick_count t0 = tick_count::now();

    const size_t N = 100000;
    string* Data = new string[N];

    for (size_t i = 0; i < N; ++i) {
        Data[i] = generateRandomString();
    }

    StringTable table;

    // put occurrences into the table
    parallel_for(blocked_range<string*>(Data, Data + N, 1000), Tally(table));

    // display the occurrences
    for (StringTable::iterator i = table.begin(); i != table.end(); ++i) {
        printf("%s -> %d\n", i->first.c_str(), i->second);
    }

    tick_count t1 = tick_count::now();
    printf("time: %g seconds\n", (t1 - t0).seconds());
    delete[] Data;
}
