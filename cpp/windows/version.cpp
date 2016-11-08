#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

/*
Windows NT 4                            4.0
Windows 2000                            5.0
Windows XP                              5.1
Windows Server 2003                     5.2
Windows Vista, Server 2008              6.0
Windows 7, Server 2008 R2               6.1
Windows 8, Server 2012                  6.2
Windows 8.1, Server 2012 R2             6.3
*/

int main(){

    OSVERSIONINFOEX osv = { sizeof(osv) };
    GetVersionEx((OSVERSIONINFO*)&osv);
    cout << "version is " << osv.dwMajorVersion << "." << osv.dwMinorVersion << endl;

    return 0;
}