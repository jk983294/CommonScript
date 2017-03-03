#include "my_utils.h"

unsigned int Factorial( unsigned int number ) {
    return number > 1 ? Factorial(number-1) * number : 1;
}

void throwIfValueTrue( bool value ){
    if(value)
        throw 1;
}
