#include <getopt.h>
#include <iostream>
#include <string>

using namespace std;

/**
 * if opt without : it means this opt does not have parameter
 * if opt with : it means this opt has parameter with an space delimiter
 * if opt with :: it means this opt has parameter with no space delimiter
 *
 * usage: ./a.out --aa -b --cc 10 -d "kun jiang"
 */

void usage();

int main(int argc, char **argv) {
    struct option opts[] = {{"aa", no_argument, nullptr, 'a'},
                            {"bb", no_argument, nullptr, 'b'},
                            {"cc", required_argument, nullptr, 'c'},
                            {"dd", required_argument, nullptr, 'd'},
                            {nullptr, 0, nullptr, 0}};

    int opt, option_index = 0;
    int intC = 0;
    bool flagA = false;
    bool flagB = false;
    string stringD;
    while ((opt = getopt_long(argc, argv, "abc::d:", opts, &option_index)) != -1) {
        switch (opt) {
            case 0:
                if (opts[option_index].flag != nullptr) break;
                switch (option_index) {
                    case 0:
                        flagA = true;
                        break;
                    case 1:
                        flagB = true;
                        break;
                    case 2:
                        intC = std::atoi(optarg);
                        break;
                    case 3:
                        stringD = std::string(optarg);
                        break;
                    default:
                        break;
                }
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
