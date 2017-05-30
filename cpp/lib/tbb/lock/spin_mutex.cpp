#include <iostream>
#include "tbb/spin_mutex.h"

using namespace tbb;
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node() {}
    Node(int d) : data(d) {}
};

Node* FreeList;  // used as allocator
typedef spin_mutex FreeListMutexType;
FreeListMutexType FreeListMutex;

Node* AllocateNode() {
    Node* n;
    {
        FreeListMutexType::scoped_lock lock(FreeListMutex);
        n = FreeList;
        if (n) FreeList = n->next;
    }
    if (!n) n = new Node();
    return n;
}

void FreeNode(Node* n) {
    FreeListMutexType::scoped_lock lock(FreeListMutex);
    n->next = FreeList;
    FreeList = n;
}

int main() {
    Node* n = AllocateNode();
    cout << n->data << endl;
    FreeNode(n);
    return 0;
}
