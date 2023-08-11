#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class MyApi {
public:
    virtual void process() = 0;
    virtual void func_dispatch(void *user_data, bool (*user_fn)(void *, int)) = 0;

    template <typename Func>
    void ForEachBid_If(Func user_fn) {
        /**
         * use below pl_fn lambda capture user_fn signature, and convert it back in virtual func_dispatch
         */
        auto pl_fn = [](void *user_data, int d) -> bool {
            auto *user_fn1 = (Func *)user_data;
            return (*user_fn1)(d);
        };
        func_dispatch((void *)&user_fn, pl_fn);
    }
};

class My : public MyApi {
public:
    virtual void process() { printf("process"); }

    virtual void func_dispatch(void *user_data, bool (*user_fn)(void *, int)) { user_fn(user_data, data); }

private:
    int data = 42;
};

int main() {
    int a = 1;
    auto bid_lambda = [&](int x) {
        a += x;
        printf("in lambda %d\n", a);
        return true;
    };

    MyApi *lob = new My();
    lob->process();
    lob->ForEachBid_If(bid_lambda);
}
