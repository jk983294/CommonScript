#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string filename{ "test.txt" };

    //ofstream ofs(filename, ofstream::out | ofstream::app);
    ofstream ofs(filename, ofstream::out | ofstream::trunc);

    if (!ofs)
    {
        cout << "open file failed" << endl;
    }
    else
    {
        ofs << "111   222" << endl;
        ofs << "333" << endl;
        ofs.close();
    }
    return 0;
}