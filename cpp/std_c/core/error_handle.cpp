#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

FILE *open_file (const char *name)
{
    FILE *stream;
    errno = 0;
    stream = fopen (name, "r");
    if (stream == NULL) {
        cerr << program_invocation_short_name << ": Couldn’t open file "
             << name << ", " << strerror (errno) << endl;
        // main: Couldn’t open file not.exist.file, No such file or directory
    }
    else
        return stream;
}

int main(){
    FILE* file = open_file("not.exist.file");
    return 0;
}
