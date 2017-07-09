#include <atomic>
#include <boost/intrusive_ptr.hpp>
#include <iostream>
#include <memory>

/**
 * intrusive_ptr has the same memory footprint as a raw ptr, and can be constructed from any T* raw pointer
 * 一个raw pointer只能创建一个shared_ptr，否则raw pointer指向的对象会被析构多次
 * 创建的intrusive_ptr，完全具备shared_ptr的功能，且不存在shared_ptr的问题，
 * 即可以利用raw pointer创建多个intrusive _ptr其原因就在ref_count对象，shared_ptr是放在shared_ptr结构里
 */

template <typename T>
struct intrusive_ptr_base {
    intrusive_ptr_base() : ref_count(0) { std::cout << "  Default constructor " << std::endl; }
    intrusive_ptr_base(intrusive_ptr_base const&) : ref_count(0) { std::cout << "  Copy constructor..." << std::endl; }
    virtual ~intrusive_ptr_base() { std::cout << "  intrusive_ptr_base destructor " << std::endl; }

    /// does not support assignment
    intrusive_ptr_base& operator=(intrusive_ptr_base const& rhs) {
        std::cout << "  assignment operator..." << std::endl;
        return *this;
    }

    friend void intrusive_ptr_add_ref(intrusive_ptr_base const* s) {
        std::cout << "  intrusive_ptr_add_ref..." << std::endl;
        assert(s->ref_count >= 0);
        assert(s != 0);
        ++s->ref_count;
    }

    friend void intrusive_ptr_release(intrusive_ptr_base const* s) {
        std::cout << "  intrusive_ptr_release..." << std::endl;
        assert(s->ref_count > 0);
        assert(s != 0);
        if (--s->ref_count == 0) delete s;
    }

    boost::intrusive_ptr<T> self() { return boost::intrusive_ptr<T>((T*)this); }
    boost::intrusive_ptr<T> self() const { return boost::intrusive_ptr<T>((T const*)this); }
    int refcount() const { return ref_count; }

private:
    // should be modifiable even from const intrusive_ptr objects
    mutable std::atomic<int> ref_count;
};

class Connection : public intrusive_ptr_base<Connection> {
public:
    Connection(int id, std::string tag) : connection_id(id), connection_tag(tag) {}
    Connection(const Connection& rhs) : connection_id(rhs.connection_id), connection_tag(rhs.connection_tag) {}

    const Connection operator=(const Connection& rhs) {
        if (this != &rhs) {
            connection_id = rhs.connection_id;
            connection_tag = rhs.connection_tag;
        }
        return *this;
    }

private:
    int connection_id;
    std::string connection_tag;
};

int main() {
    std::cout << "Create an intrusive ptr" << std::endl;
    boost::intrusive_ptr<Connection> con0(new Connection(4, "sss"));
    std::cout << "Create an intrusive ptr. Refcount = " << con0->refcount() << std::endl;
    boost::intrusive_ptr<Connection> con1(con0);
    std::cout << "Create an intrusive ptr. Refcount = " << con1->refcount() << std::endl;
    boost::intrusive_ptr<Connection> con2 = con0;
    std::cout << "Create an intrusive ptr. Refcount = " << con2->refcount() << std::endl;

    std::cout << "Create an intrusive ptr. Refcount = " << con2->refcount() << std::endl;
    std::cout << "Destroy an intrusive ptr" << std::endl;
    return 0;
}
