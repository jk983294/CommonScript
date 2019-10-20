/**
 * gcc -c main.c
 * gcc -o main1 main.o -L. -Wl,-rpath=. -lwrap -lfirst -lsecond -ldl
 * gcc -o main2 main.o -L. -Wl,-rpath=. -lwrap -lsecond -lfirst -ldl
 */

void print_message();
void first();
void second();

int main() {
    first();
    second();
    print_message();
    return 0;
}
