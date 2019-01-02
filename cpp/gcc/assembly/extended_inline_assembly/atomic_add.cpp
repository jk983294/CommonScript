#include <iostream>

using namespace std;

void unconditional_atomic_add() {
    int my_var = 1;
    int my_int = 2;
    __asm__ __volatile__(
        "   lock       ;\n"
        "   addl %1,%0 ;\n"
        : "=m"(my_var)
        : "ir"(my_int), "m"(my_var)
        : /* no clobber-list */
        );
    cout << "unconditional_atomic_add " << my_var << " " << my_int << endl;
}

// my_var is decremented by one and if the resulting value is 0 then, the variable cond is set.
void atomic_conditional_change() {
    int my_var = 1;
    bool cond = false;
    __asm__ __volatile__(
        "   lock       ;\n"
        "decl %0; sete %1"
        : "=m"(my_var), "=q"(cond)
        : "m"(my_var)
        : "memory");
    cout << "atomic_conditional_change " << cond << " " << my_var << endl;
}

int main() {
    unconditional_atomic_add();
    atomic_conditional_change();
    return 0;
}
