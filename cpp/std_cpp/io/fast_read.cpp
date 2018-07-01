#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <chrono>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>

using namespace std;
using namespace chrono;

const int MAXN = 10000000;
int numbers[MAXN];
const string filename{"/tmp/test.txt"};

void generate_test_data() {
    ofstream ofs(filename, ofstream::out | ofstream::trunc);

    if (!ofs) {
        cerr << "open file failed" << endl;
    } else {
        for (int i = 0; i < MAXN; ++i) {
            ofs << i << '\n';
        }
        ofs.close();
    }
}

void scanf_read() {
    freopen(filename.c_str(), "r", stdin);
    for (int i = 0; i < MAXN; i++) scanf("%d", &numbers[i]);
}

void cin_read() {
    freopen(filename.c_str(), "r", stdin);
    for (int i = 0; i < MAXN; i++) std::cin >> numbers[i];
}

void cin_read_nosync() {
    freopen(filename.c_str(), "r", stdin);
    std::ios::sync_with_stdio(false);
    for (int i = 0; i < MAXN; i++) std::cin >> numbers[i];
}

const int BufferSize = 60 * 1024 * 1024;
char buf[BufferSize];

void analyse(char *buf, int len = BufferSize) {
    int i;
    numbers[i = 0] = 0;
    for (char *p = buf; *p && p - buf < len; p++)
        if (*p == '\n')
            numbers[++i] = 0;
        else
            numbers[i] = numbers[i] * 10 + *p - '0';
}

void fread_analyse() {
    freopen(filename.c_str(), "rb", stdin);
    int len = static_cast<int>(fread(buf, 1, BufferSize, stdin));
    buf[len] = '\0';
    analyse(buf, len);
}

void mmap_analyse() {
    int fd = open(filename.c_str(), O_RDONLY);
    int len = static_cast<int>(lseek(fd, 0, SEEK_END));
    char *mbuf = (char *)mmap(NULL, static_cast<size_t>(len), PROT_READ, MAP_PRIVATE, fd, 0);
    analyse(mbuf, len);
}

void test_time(function<void()> f, string desc) {
    auto begin = chrono::high_resolution_clock::now();
    f();
    auto end = chrono::high_resolution_clock::now();
    cout << desc << " took up " << chrono::duration_cast<microseconds>(end - begin).count() << " us" << endl;
}

int main() {
    test_time(generate_test_data, "generate_test_data");  // 678829 us
    test_time(scanf_read, "scanf_read");                  // 988529 us
    test_time(cin_read, "cin_read");                      // 2867377 us
    test_time(cin_read_nosync, "cin_read_nosync");        // 725997 us 与scanf效率相差无几
    test_time(fread_analyse, "fread");                    // 215207 us 读入整个文件再处理的方法
    test_time(mmap_analyse, "mmap");                      // 244180 us map整个文件再处理的方法
    return 0;
}
