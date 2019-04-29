#include <libgen.h>
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    /**
     * basename dirname all need new space since they are destructive
     */
    char *path = strdupa(argv[0]);
    cout << basename(path) << endl;     // utils
    cout << basename("") << endl;       // .
    cout << basename(nullptr) << endl;  // .
    path = strdupa("////");
    cout << basename(path) << endl;  // /
    path = strdupa("/a/b/kun/");
    cout << basename(path) << endl;  // kun

    cout << dirname(argv[0]) << endl;  // .
    cout << dirname("") << endl;       // .
    cout << dirname(nullptr) << endl;  // .
    path = strdupa("////");
    cout << dirname(path) << endl;  // /
    path = strdupa("/a/b/kun/");
    cout << dirname(path) << endl;  // /a/b

    /**
     * random string, it is in place random
     */
    char source[] = "1234567890";
    char *dest = nullptr;
    dest = (char *)strfry(source);
    cout << dest << " " << reinterpret_cast<uint64_t>(source) << " " << reinterpret_cast<uint64_t>(dest) << endl;
    return 0;
}
