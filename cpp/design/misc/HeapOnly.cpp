#include <string>
#include <iostream>
#include <memory>

using namespace std;

class HeapOnly {
private:
    ~HeapOnly(){}
public:
    void destroy(){
        delete this;
    }
};

int main()
{
    // HeapOnly heapOnly;
    HeapOnly* heapOnly = new HeapOnly();
    heapOnly->destroy();
    return 0;
}