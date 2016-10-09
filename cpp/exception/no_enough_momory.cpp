#include <iostream>
#include <typeinfo>
#include <exception>

using namespace std;

// function to call if operator new can't allocate enough memory
void no_more_memory() {
    cerr << "unable to satisfy request for memory" << endl;
}

template<typename T>
class NewHandlerSupport {
public:
    static new_handler set_new_handler(new_handler p);
    static void * operator new(size_t size);
private:
    static new_handler currentHandler;
};
template<typename T>
new_handler NewHandlerSupport<T>::set_new_handler(new_handler p)
{
    new_handler oldHandler = currentHandler;
    currentHandler = p;
    return oldHandler;
}

template<typename T>
void * NewHandlerSupport<T>::operator new(size_t size){
    new_handler globalHandler =	std::set_new_handler(currentHandler);	    // install new new_handler
    void *memory;

    try {
        memory = ::operator new(size);
    } catch (std::bad_alloc&) { 	                                        // restore old new_handler
        std::set_new_handler(globalHandler);
        throw;
    }
    std::set_new_handler(globalHandler);	                                // restore old new_handler
    return memory;
}
// this sets each currentHandler to nullptr
template<typename T>
new_handler NewHandlerSupport<T>::currentHandler;


class x: public NewHandlerSupport<x> {
};

int main(){
    x::set_new_handler(no_more_memory);
    x *px1 = new x;                                                         // call no_more_memory
    string *ps = new string;                                                // call global new-handling when failed

    x::set_new_handler(0);                                                  // set x's new-handling null
    x *px2 = new x;                                                         // throw bad_alloc exception
    return 0;
}