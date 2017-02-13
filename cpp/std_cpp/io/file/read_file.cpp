#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string filename{ "test.txt" };
    ifstream ifs(filename, ifstream::in);

    if (ifs.is_open())
    {
        string s;
        while (getline(ifs, s))
        {
            cout << s << endl;
        }

        ifs.close();
    }
    return 0;
}