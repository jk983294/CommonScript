#include <stdio.h>

/**
 * n++
 * type __sync_fetch_and_add(type *ptr, type value, ...); // m + n
 * type __sync_fetch_and_sub(type *ptr, type value, ...); // m - n
 * type __sync_fetch_and_or(type *ptr, type value, ...);  // m | n
 * type __sync_fetch_and_and(type *ptr, type value, ...); // m & n
 * type __sync_fetch_and_xor(type *ptr, type value, ...); // m ^ n
 * type __sync_fetch_and_nand(type *ptr, type value, ...); // (~m) & n
 *
 * ++n
 * type __sync_add_and_fetch(type *ptr, type value, ...); // m + n
 * type __sync_sub_and_fetch(type *ptr, type value, ...); // m - n
 * type __sync_or_and_fetch(type *ptr, type value, ...); // m | n
 * type __sync_and_and_fetch(type *ptr, type value, ...); // m & n
 * type __sync_xor_and_fetch(type *ptr, type value, ...); // m ^ n
 * type __sync_nand_and_fetch(type *ptr, type value, ...); // (~m) & n
 *
 * CAS
 * bool __sync_bool_compare_and_swap (type *ptr, type oldval, type newval, ...);
 * type __sync_val_compare_and_swap (type *ptr, type oldval, type newval, ...);
 */

int main() {
    int num = 0;

    /*
     * n++;
     * __sync_fetch_and_add(10, 3) = 10
     * num = 13
     */
    num = 10;
    printf("__sync_fetch_and_add(%d, %d) = %d\n", 10, 3, __sync_fetch_and_add(&num, 3));
    printf("num = %d\n", num);

    /*
     * ++n;
     * __sync_and_add_and_fetch(10, 3) = 13
     * num = 13
     */
    num = 10;
    printf("__sync_add_and_fetch(%d, %d) = %d\n", 10, 3, __sync_add_and_fetch(&num, 3));
    printf("num = %d\n", num);

    /*
     * CAS, match
     * __sync_val_compare_and_swap(10, 10, 2) = 10
     * num = 2
     */
    num = 10;
    printf("__sync_val_compare_and_swap(%d, %d, %d) = %d\n", 10, 10, 2, __sync_val_compare_and_swap(&num, 10, 2));
    printf("num = %d\n", num);

    /*
     * CAS, not match
     * __sync_val_compare_and_swap(10, 3, 5) = 10
     * num = 10
     */
    num = 10;
    printf("__sync_val_compare_and_swap(%d, %d, %d) = %d\n", 10, 3, 5, __sync_val_compare_and_swap(&num, 1, 2));
    printf("num = %d\n", num);

    return 0;
}
