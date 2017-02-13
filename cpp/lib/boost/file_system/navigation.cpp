#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost;
using namespace boost::filesystem;

void dir_nav(path& dir)
{
    directory_iterator end;
    for (directory_iterator i(dir); i != end; ++i)
    {
        path p = i->path();

        if (is_regular_file(p))
            cout << p.filename() << endl;
        else if (is_directory(p))
        {
            cout << "directory " << p.filename() << endl;
            dir_nav(p);
        }
    }
}
int main(int argc, char *argv[])
{
    cout << boolalpha;

    path dir("E:/SysinternalsSuite");

    dir_nav(dir);

    getchar();
    return 0;
}