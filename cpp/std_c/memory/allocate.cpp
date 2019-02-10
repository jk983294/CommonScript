#include <iostream>

using namespace std;

int main()
{
    void* p1 = malloc(16);
    free(p1);

    /**
     * Changing the Size of a Block
     * If the block needs to be moved, realloc copies the old contents.
     * if it decide to realloc in new space, then old one will be freed automatically
     */
    p1 = malloc(16);
    p1 = realloc(p1, 32);
    free(p1);

    /**
     * Allocating Cleared Space
     * it allocates memory and clears it to zero.
     */
    p1 = calloc(sizeof(int), 10); // alloc 10 int, all init to 0
    int* p2 = reinterpret_cast<int*>(p1);
    cout << *p2 << " " << *(p2 + 9) << endl;
    free(p1);
    return 0;
}
