#include <string>
#include <iostream>
#include <memory>

using namespace std;

class StackOnly {
private:
    void* operator new (size_t size) = delete;
    void *operator new[](size_t size) = delete;
public:
    int x;
};

int main()
{
    StackOnly stackOnly;
    //StackOnly* stackOnly1 = new StackOnly();
    return 0;
}