/*****************************************************************************\
    to support factory method for your class:

    1) inherit from FactoryObject
    2) add line SUPPORT_FACTORY_DECLARE(class_name, "class_name") in
       you class definition
    3) add line SUPPORT_FACTORY_IMPLEMENT(class_name) on your
       .cpp file.

    That's it. You can now use FactoryObject::sInstanceof("class_name")
    to create an instance of your class.
\****************************************************************************/

#ifndef _FACTORYOBJECT_H_
#define _FACTORYOBJECT_H_

#include <map>
#include <string>

//using namespace std;

class FactoryObject
{
public:

    FactoryObject(void) {}
    virtual ~FactoryObject(void) {}

    static FactoryObject* sInstanceOf(const std::string& aObjectName);

    static void sRegisterObject(
        const std::string& aObjectName, const FactoryObject& aObject);

    virtual void readSettings(const std::string& aSettings) {};
    virtual FactoryObject* newInstance(void) const = 0;

    const std::string& name() const { return _name; }

protected:

    typedef std::map<std::string, const FactoryObject*> _objectMap;

    class ObjectMap : public _objectMap
    {
    public:

        virtual ~ObjectMap(void);
    };

    static ObjectMap* sObjectMap;

    class _internalUseOnly;
    static _internalUseOnly* _donnotusethis;
    std::string _name;
};

#define SUPPORT_FACTORY_DECLARE(object_name, register_name) \
    private: \
        static object_name sObjectForRegister; \
        object_name(_internalUseOnly*) { sRegisterObject(register_name, *this); } \
    public: \
        virtual FactoryObject* newInstance(void) const { return new object_name; }

#define SUPPORT_FACTORY_IMPLEMENT(object_name) \
    object_name object_name::sObjectForRegister(_donnotusethis);


struct MyObj : public FactoryObject {
    virtual ~MyObj() = default;
    virtual void process() = 0;
    static MyObj* create(const std::string& name);
};

#endif	
