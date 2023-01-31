#include <cstring>
#include <stdexcept>
#include <string>
#include <dlfcn.h>
#include <unistd.h>
#include <FactoryObject.h>

using namespace std;

void* create_from_so(const std::string& so_path) {
    typedef void* (*create_object_t)();
    void* pModule = dlopen(so_path.c_str(), RTLD_LAZY);
    if (pModule == nullptr) {
        printf("error: cannot open %s Error msg: %s\n", so_path.c_str(), dlerror());
        return nullptr;
    }
    auto create_func = (create_object_t)dlsym(pModule, "create");
    if (create_func == nullptr) {
        printf("no create function found in module %s\n", so_path.c_str());
        return nullptr;
    }
    return create_func();
}

int main() {
    MyObj* obj1 = (MyObj*)create_from_so("libshared1.so");
    MyObj* obj2 = (MyObj*)create_from_so("libshared2.so");
    obj1->process();
    obj2->process();
}