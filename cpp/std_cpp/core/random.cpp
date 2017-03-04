#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    int ran_num;
    for(int i = 0; i < 10; i++){
        ran_num = rand() % 6;               // get pesudo random number [0, 6)
        cout << ran_num << endl;
    }

    srand((unsigned)time(0));
    for(int i = 0; i < 10; i++){
        ran_num = rand() % 6;               // get time random number [0, 6)
        cout << ran_num << endl;
    }
    return 0;
}
