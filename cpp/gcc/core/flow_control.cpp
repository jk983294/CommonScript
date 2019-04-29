#include <setjmp.h>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

/**
 * Non-Local Exits
 * identify return points for non-local exits by calling the function setjmp
 * setjmp longjmp
 */

jmp_buf main_loop;

void abort_to_main_loop(int status) { longjmp(main_loop, status); }

void do_command() {
    string buffer;
    cin >> buffer;
    if (buffer == "e") {
        cout << "exit program\n";
        exit(0);
    } else {
        /**
         * go back to main loop's that line where setjmp called
         * and that line return -1 instead of return 0 for the first time
         */
        abort_to_main_loop(-1);
    }
}

int main() {
    while (1) {
        if (setjmp(main_loop)) {  // this record this line to main_loop, success call return 0 and then do_command()
            cout << "back at main loop....\n";  // do clean up from next time
        } else {
            cout << "do_command\n";
            do_command();
        }
    }
}
