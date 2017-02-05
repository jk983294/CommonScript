#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool check_file_exists(const char* path)
{
    fstream ifs(path, ios::in);
    if (ifs)
    {
        ifs.close();
        return true;
    }
    return false;
}

int main() {
    string filename{ "test.txt" };

    cout << check_file_exists(filename.c_str()) << endl;

    return 0;
}