#include <cstddef>
#include <iostream>

using namespace std;

#define STRINGIFY(arg) #arg
#define CONCATENATE(arg1, arg2) arg1##arg2

/**
 * PRINT_OFFSETS will print offset of each of the fields within structure passed as the first argument
 * the idea is calculate the argument count N
 * then dispatch to macro PRINT_OFFSETS_{N}
 * then PRINT_OFFSETS_{N} handle one field and dispatch the rest to PRINT_OFFSETS_{N - 1}
 */
#define PRINT_OFFSETS_1(structure, field, ...) \
    printf(STRINGIFY(structure) ":" STRINGIFY(field) "-%zu\n", offsetof(structure, field));
#define PRINT_OFFSETS_2(structure, field, ...)                                              \
    printf(STRINGIFY(structure) ":" STRINGIFY(field) "-%zu\n", offsetof(structure, field)); \
    PRINT_OFFSETS_1(structure, __VA_ARGS__)
#define PRINT_OFFSETS_3(structure, field, ...)                                              \
    printf(STRINGIFY(structure) ":" STRINGIFY(field) "-%zu\n", offsetof(structure, field)); \
    PRINT_OFFSETS_2(structure, __VA_ARGS__)
#define PRINT_OFFSETS_4(structure, field, ...)                                              \
    printf(STRINGIFY(structure) ":" STRINGIFY(field) "-%zu\n", offsetof(structure, field)); \
    PRINT_OFFSETS_3(structure, __VA_ARGS__)
#define PRINT_OFFSETS_5(structure, field, ...)                                              \
    printf(STRINGIFY(structure) ":" STRINGIFY(field) "-%zu\n", offsetof(structure, field)); \
    PRINT_OFFSETS_4(structure, __VA_ARGS__)
#define PRINT_OFFSETS_6(structure, field, ...)                                              \
    printf(STRINGIFY(structure) ":" STRINGIFY(field) "-%zu\n", offsetof(structure, field)); \
    PRINT_OFFSETS_5(structure, __VA_ARGS__)
#define PRINT_OFFSETS_7(structure, field, ...)                                              \
    printf(STRINGIFY(structure) ":" STRINGIFY(field) "-%zu\n", offsetof(structure, field)); \
    PRINT_OFFSETS_6(structure, __VA_ARGS__)
#define PRINT_OFFSETS_8(structure, field, ...)                                              \
    printf(STRINGIFY(structure) ":" STRINGIFY(field) "-%zu\n", offsetof(structure, field)); \
    PRINT_OFFSETS_7(structure, __VA_ARGS__)

// below used to get variadic argument number
#define PP_NARG(...) PP_NARG_(__VA_ARGS__, PP_RSEQ_N())
#define PP_NARG_(...) PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define PP_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0

#define PRINT_OFFSETS_(N, structure, field, ...) CONCATENATE(PRINT_OFFSETS_, N)(structure, field, __VA_ARGS__)
#define PRINT_OFFSETS(structure, field, ...) PRINT_OFFSETS_(PP_NARG(field, __VA_ARGS__), structure, field, __VA_ARGS__)

struct A {
    int a;
    int b;
    int c;
};

int main() {
    cout << PP_NARG(a, b, c) << endl;  // 3
    PRINT_OFFSETS(A, a, b, c);
    return 0;
}
