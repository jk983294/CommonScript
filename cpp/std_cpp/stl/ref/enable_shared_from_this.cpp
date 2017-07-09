#include <iostream>
#include <memory>

/**
 * enable_shared_from_this enables you to get a valid shared_ptr instance to this
 * otherwise each shared_ptr thinks it's the only owner of this object by return std::shared_ptr<T>(this);
 */

struct Good : std::enable_shared_from_this<Good> {
    std::shared_ptr<Good> getptr() { return shared_from_this(); }
};

struct Bad {
    std::shared_ptr<Bad> getptr() { return std::shared_ptr<Bad>(this); }
    ~Bad() { std::cout << "Bad::~Bad() called\n"; }
};

int main() {
    // Good: the two shared_ptr's share the same object
    std::shared_ptr<Good> gp1 = std::make_shared<Good>();
    std::shared_ptr<Good> gp2 = gp1->getptr();
    std::cout << "gp2.use_count() = " << gp2.use_count() << '\n';
    if (!gp1.owner_before(gp2) && !gp2.owner_before(gp1)) std::cout << "gp1 and gp2 share ownership" << '\n';

    // Bad: object not managed by shared_ptr which will cause double deletion
    try {
        Good not_so_good;  // this is not a shared_ptr which cause problem
        std::shared_ptr<Good> gp1 = not_so_good.getptr();
    } catch (std::bad_weak_ptr& e) {
        std::cout << e.what() << '\n';
    }

    // Bad, each shared_ptr thinks it's the only owner of the object, which will cause double deletion
    std::shared_ptr<Bad> bp1 = std::make_shared<Bad>();
    std::shared_ptr<Bad> bp2 = bp1->getptr();
    std::cout << "bp2.use_count() = " << bp2.use_count() << '\n';
}
