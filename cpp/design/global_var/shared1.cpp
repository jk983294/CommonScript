#include <FactoryObject.h>


struct MyObjDerived : public MyObj {
    SUPPORT_FACTORY_DECLARE(MyObjDerived, "MyObjDerived")

    int m_data{1};

    MyObjDerived() = default;
    virtual void process() override {
        printf("MyObjDerived1 %d\n", m_data);
    }
};

SUPPORT_FACTORY_IMPLEMENT(MyObjDerived)


extern "C" {
MyObj* create() { return new MyObjDerived; }
}