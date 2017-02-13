#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost;
using namespace boost::filesystem;


int main(int argc, char *argv[])
{
    cout << boolalpha;
    path file1("E:/log.txt");
    cout << exists(file1) << endl;
    cout << is_regular_file(file1) << endl;
    cout << file_size(file1) << endl;
    cout << file1.filename() << endl;
    cout << file1.filename().replace_extension() << endl;

    auto s = status(file1);
    auto t = s.type();
    auto ps = s.permissions();
    cout << "type is " << t << endl;
    if ((ps & owner_write) != owner_write)
        cout << "no perm to write" << endl;

    cout << "============================" << endl;
    path dir("E:/GitHub");
    path root = dir.root_path();
    cout << root << endl;
    cout << exists(dir) << endl;
    cout << is_regular_file(dir) << endl;
    cout << is_directory(dir) << endl;
    cout << dir.string() << endl;

    cout << "============================" << endl;
    for (auto& child : dir)
    {
        cout << child << endl;
    }

    try
    {
        path p("junk");
        cout << file_size(p) << endl;
    }
    catch (const filesystem_error& e)
    {
        cout << e.what() << endl;
    }

    getchar();
    return 0;
}