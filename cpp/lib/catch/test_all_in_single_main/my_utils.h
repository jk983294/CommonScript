#ifndef MY_UTILS_H
#define MY_UTILS_H

unsigned int Factorial( unsigned int number );
void throwIfValueTrue( bool value );

template<typename T>
T getValue( T value ){
    return value;
}

#endif
