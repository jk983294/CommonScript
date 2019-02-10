#include <iostream>
#include <cstring>
#include <fcntl.h>

using namespace std;

/**
 * alloca supports half-dynamic allocation in which blocks are allocated dynamically but freed automatically.
 * Do not use alloca inside the arguments of a function call like foo (x, alloca(4), y)
 */

int open_v1 (const char *str1, const char *str2, int flags, int mode)
{
    char *name = (char *) alloca (strlen (str1) + strlen (str2) + 1);   // no need to free this space
    stpcpy (stpcpy (name, str1), str2);
    return open (name, flags, mode);
}

int open_v2 (const char *str1, const char *str2, int flags, int mode)
{
    char name[strlen (str1) + strlen (str2) + 1]; // Variable-Size Arrays instead of alloca
    stpcpy (stpcpy (name, str1), str2);
    return open (name, flags, mode);
}

int main()
{
    int fd = open_v1("/tmp/", "a.txt", 0, 0x777);
    cout << fd << endl;
    fd = open_v2("/tmp/", "a.txt", 0, 0x777);
    cout << fd << endl;
    return 0;
}
