#ifndef EXTERN_C_H
#define EXTERN_C_H

/**
 * do not mangle function name
 */
#ifdef __cplusplus
extern "C" {
#endif

    int bar( int x, int y );

#ifdef __cplusplus
}
#endif

extern "C" {
    int foo( int x, int y );
}

extern "C" int meow( int x, int y );


#endif //EXTERN_C_H