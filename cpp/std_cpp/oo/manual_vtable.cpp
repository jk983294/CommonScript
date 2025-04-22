#include <iostream>
#include <vector>

struct Operation {
    using func_type = void(*)(Operation*);
    func_type func_{nullptr};
    Operation* next_{nullptr};

    Operation(func_type func): func_{func} {}
    void perform() {
        func_(this);
    }
};

class T0Op : public Operation {
public:
    T0Op() : Operation(&T0Op::impl) {}
    void work() {
        std::cout << "T0Op work\n";
    }

private:
    static void impl(Operation* op) {
        static_cast<T0Op*>(op)->work();
    }
};

class T1Op : public Operation {
public:
    T1Op() : Operation(&T1Op::impl) {}
    void work() {
        std::cout << "T1Op work\n";
    }

private:
    static void impl(Operation* op) {
        static_cast<T1Op*>(op)->work();
    }
};

int main() {
    T0Op op0;
    T1Op op1;
    op0.next_ = &op1;
    Operation* pOp = &op0;
    while (pOp) {
        pOp->perform();
        pOp = pOp->next_;
    }
}