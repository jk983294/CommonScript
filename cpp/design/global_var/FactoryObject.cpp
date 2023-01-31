#include "FactoryObject.h"
#include <iostream>

FactoryObject::ObjectMap* FactoryObject::sObjectMap;

FactoryObject* 
FactoryObject::sInstanceOf(const std::string& aObjectName)
{
	if (!sObjectMap) 
    {
        std::cout << "sObjectMap not created\n";
        return NULL;
    }

    ObjectMap::iterator it = sObjectMap->find(aObjectName);
    if (it != sObjectMap->end() && (*it).second)
    {
        FactoryObject* obj = (*it).second->newInstance();
        obj->_name = aObjectName;
        return obj;
    }
    else
    {
        std::cout << aObjectName << " no defined in Factory map\n";
    }

    return NULL;
}
 
void 
FactoryObject::sRegisterObject(
const std::string& aObjectName, const FactoryObject& aObject)
{
	if (!sObjectMap) sObjectMap = new ObjectMap;
    (*sObjectMap)[aObjectName] = &aObject;
}

FactoryObject::ObjectMap::~ObjectMap(void)
{
    for (iterator it = begin(); it != end(); ++it)
        delete (*it).second;
}

FactoryObject::_internalUseOnly* FactoryObject::_donnotusethis;

MyObj* MyObj::create(const std::string& className)
{
    MyObj* stat = dynamic_cast<MyObj*>(sInstanceOf(className));
    return stat;
}
