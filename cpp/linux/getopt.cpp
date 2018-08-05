#include <unistd.h>
#include <iostream>

using namespace std;

/**
 * if opt without : it means this opt does not have parameter
 * if opt with : it means this opt has parameter with an space delimiter
 * if opt with :: it means this opt has parameter with no space delimiter
 *
 * usage: ./a.out -a -b -c10 -d "kun jiang"
 */

void usage();

int main(int argc, char **argv) {
    int opt, intC = 0;
    bool flagA = false;
    bool flagB = false;
    string stringD;
    while ((opt = getopt(argc, argv, "abc::d:")) != -1) {
        switch (opt) {
            case 'a':
                flagA = true;
                break;
            case 'b':
                flagB = true;
                break;
            case 'c':
                intC = std::atoi(optarg);
                break;
            case 'd':
                stringD = std::string(optarg);
                break;
            case '?':
                usage();
            default:
                abort();
        }
    }

    cout << flagA << " " << flagB << " " << intC << " " << stringD << " " << endl;
    return 0;
}

void usage() { cout << "usage:\n -a for enabling a \n -b for enabling b \n -c<value> \n -d <value>\n"; }
