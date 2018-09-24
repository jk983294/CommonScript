#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

namespace reflect {

// Base class of all type descriptors
struct TypeDescriptor {
    const char* name;
    size_t size;

    TypeDescriptor(const char* name, size_t size) : name{name}, size{size} {}
    virtual ~TypeDescriptor() {}
    virtual std::string getFullName() const { return name; }
    virtual void dump(const void* obj, size_t indentLevel = 0) const = 0;
};

// Declare the function template that handles primitive types such as int, std::string, etc.
template <typename T>
TypeDescriptor* getPrimitiveDescriptor();

// A helper class to find TypeDescriptors in different ways:
struct DefaultResolver {
    template <typename T>
    static char func(decltype(&T::Reflection));
    template <typename T>
    static int func(...);

    template <typename T>
    struct IsReflected {
        enum { value = (sizeof(func<T>(nullptr)) == sizeof(char)) };  // T with Reflection eval to true
    };

    // This version is called if T has a static member named "Reflection":
    template <typename T, typename std::enable_if<IsReflected<T>::value, int>::type = 0>
    static TypeDescriptor* get() {
        return &T::Reflection;
    }

    // This version is called otherwise:
    template <typename T, typename std::enable_if<!IsReflected<T>::value, int>::type = 0>
    static TypeDescriptor* get() {
        return getPrimitiveDescriptor<T>();
    }
};

// This is the primary class template for finding all TypeDescriptors:
template <typename T>
struct TypeResolver {
    static TypeDescriptor* get() { return DefaultResolver::get<T>(); }
};

// Type descriptors for user-defined structs/classes
struct TypeDescriptorStruct : TypeDescriptor {
    struct Member {
        const char* name;
        size_t offset;
        TypeDescriptor* type;
    };

    std::vector<Member> members;

    TypeDescriptorStruct(void (*init)(TypeDescriptorStruct*)) : TypeDescriptor{nullptr, 0} { init(this); }

    TypeDescriptorStruct(const char* name, size_t size, const std::initializer_list<Member>& init)
        : TypeDescriptor{nullptr, 0}, members{init} {}

    virtual void dump(const void* obj, size_t indentLevel) const override {
        std::cout << "{" << std::endl;
        size_t len = members.size();
        for (size_t i = 0; i < len; ++i) {
            const Member& member = members[i];
            std::cout << std::string(4 * (indentLevel + 1), ' ') << "\"" << member.name << "\" : ";
            member.type->dump((char*)obj + member.offset, indentLevel + 1);
            std::cout << (i == len - 1 ? " " : ",") << std::endl;
        }
        std::cout << std::string(4 * indentLevel, ' ') << "}";
    }
};

// Type descriptors for std::vector
struct TypeDescriptorStdVector : TypeDescriptor {
    TypeDescriptor* itemType;
    size_t (*getSize)(const void*);
    const void* (*getItem)(const void*, size_t);

    template <typename ItemType>
    TypeDescriptorStdVector(ItemType*)
        : TypeDescriptor{"std::vector<>", sizeof(std::vector<ItemType>)}, itemType{TypeResolver<ItemType>::get()} {
        getSize = [](const void* vecPtr) -> size_t {
            const auto& vec = *(const std::vector<ItemType>*)vecPtr;
            return vec.size();
        };
        getItem = [](const void* vecPtr, size_t index) -> const void* {
            const auto& vec = *(const std::vector<ItemType>*)vecPtr;
            return &vec[index];
        };
    }
    virtual std::string getFullName() const override {
        return std::string("std::vector<") + itemType->getFullName() + ">";
    }

    virtual void dump(const void* obj, size_t indentLevel) const override {
        size_t numItems = getSize(obj);
        if (numItems == 0) {
            std::cout << "[]";
        } else {
            std::cout << "[" << std::endl;
            for (size_t index = 0; index < numItems; index++) {
                std::cout << std::string(4 * (indentLevel + 1), ' ');
                itemType->dump(getItem(obj, index), indentLevel + 1);
                std::cout << (index == numItems - 1 ? " " : ",") << std::endl;
            }
            std::cout << std::string(4 * indentLevel, ' ') << "]";
        }
    }
};

// Partially specialize TypeResolver<> for std::vectors:
template <typename T>
class TypeResolver<std::vector<T>> {
public:
    static TypeDescriptor* get() {
        static TypeDescriptorStdVector typeDesc{(T*)nullptr};
        return &typeDesc;
    }
};

// A type descriptor for int
struct TypeDescriptorInt : TypeDescriptor {
    TypeDescriptorInt() : TypeDescriptor{"int", sizeof(int)} {}
    virtual void dump(const void* obj, size_t /* unused */) const override { std::cout << *(const int*)obj; }
};

template <>
TypeDescriptor* getPrimitiveDescriptor<int>() {
    static TypeDescriptorInt typeDesc;
    return &typeDesc;
}

// A type descriptor for std::string
struct TypeDescriptorStdString : TypeDescriptor {
    TypeDescriptorStdString() : TypeDescriptor{"std::string", sizeof(std::string)} {}
    virtual void dump(const void* obj, size_t /* unused */) const override {
        std::cout << "\"" << *(const std::string*)obj << "\"";
    }
};

template <>
TypeDescriptor* getPrimitiveDescriptor<std::string>() {
    static TypeDescriptorStdString typeDesc;
    return &typeDesc;
}

struct TypeDescriptorStdUniquePtr : TypeDescriptor {
    TypeDescriptor* targetType;             // underlying type descriptor
    const void* (*getTarget)(const void*);  // lambda to get underlying content address

    // Template constructor:
    template <typename TargetType>
    TypeDescriptorStdUniquePtr(TargetType* /* dummy argument */)
        : TypeDescriptor{"std::unique_ptr<>", sizeof(std::unique_ptr<TargetType>)},
          targetType{TypeResolver<TargetType>::get()} {
        getTarget = [](const void* uniquePtrPtr) -> const void* {
            const auto& uniquePtr = *(const std::unique_ptr<TargetType>*)uniquePtrPtr;
            return uniquePtr.get();
        };
    }

    virtual void dump(const void* obj, size_t indentLevel) const override {
        const void* targetObj = getTarget(obj);
        if (targetObj == nullptr) {
            std::cout << "null";
        } else {
            targetType->dump(targetObj, indentLevel);
            std::cout << std::string(static_cast<size_t>(4 * indentLevel), ' ');
        }
    }
};

// Partially specialize TypeResolver<> for std::unique_ptr<>:
template <typename T>
class TypeResolver<std::unique_ptr<T>> {
public:
    static TypeDescriptor* get() {
        static TypeDescriptorStdUniquePtr typeDesc{(T*)nullptr};
        return &typeDesc;
    }
};
}

#define REFLECT()                                    \
    friend struct reflect::DefaultResolver;          \
    static reflect::TypeDescriptorStruct Reflection; \
    static void initReflection(reflect::TypeDescriptorStruct*);

#define STRINGIFY(arg) #arg
#define CONCATENATE(arg1, arg2) arg1##arg2

#define REFLECT_MEMBER_1(field, ...) {#field, offsetof(T, field), reflect::TypeResolver<decltype(T::field)>::get()},
#define REFLECT_MEMBER_2(field, ...) \
    {#field, offsetof(T, field), reflect::TypeResolver<decltype(T::field)>::get()}, REFLECT_MEMBER_1(__VA_ARGS__)
#define REFLECT_MEMBER_3(field, ...) \
    {#field, offsetof(T, field), reflect::TypeResolver<decltype(T::field)>::get()}, REFLECT_MEMBER_2(__VA_ARGS__)
#define REFLECT_MEMBER_4(field, ...) \
    {#field, offsetof(T, field), reflect::TypeResolver<decltype(T::field)>::get()}, REFLECT_MEMBER_3(__VA_ARGS__)
#define REFLECT_MEMBER_5(field, ...) \
    {#field, offsetof(T, field), reflect::TypeResolver<decltype(T::field)>::get()}, REFLECT_MEMBER_4(__VA_ARGS__)
#define REFLECT_MEMBER_6(field, ...) \
    {#field, offsetof(T, field), reflect::TypeResolver<decltype(T::field)>::get()}, REFLECT_MEMBER_5(__VA_ARGS__)

// below used to get variadic argument number
#define PP_NARG(...) PP_NARG_(__VA_ARGS__, PP_RSEQ_N())
#define PP_NARG_(...) PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define PP_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0

#define REFLECT_MEMBER_(N, field, ...) CONCATENATE(REFLECT_MEMBER_, N)(field, __VA_ARGS__)
#define REFLECT_MEMBER_DEFINE(field, ...) REFLECT_MEMBER_(PP_NARG(field, __VA_ARGS__), field, __VA_ARGS__)

#define REFLECT_STRUCT_DEFINE(type, field, ...)                           \
    reflect::TypeDescriptorStruct type::Reflection{type::initReflection}; \
    void type::initReflection(reflect::TypeDescriptorStruct* typeDesc) {  \
        using T = type;                                                   \
        typeDesc->name = #type;                                           \
        typeDesc->size = sizeof(T);                                       \
        typeDesc->members = {REFLECT_MEMBER_DEFINE(field, __VA_ARGS__)};  \
    }

struct Object {
    std::string key;
    int value;
    std::unique_ptr<Object> next;

    Object(const std::string& key_, int value_, std::unique_ptr<Object> next_)
        : key(key_), value(value_), next(std::move(next_)) {}

    friend struct reflect::DefaultResolver;
    static reflect::TypeDescriptorStruct Reflection;
    static void initReflection(reflect::TypeDescriptorStruct*);
};

reflect::TypeDescriptorStruct Object::Reflection{Object::initReflection};

void Object::initReflection(reflect::TypeDescriptorStruct* typeDesc) {
    using T = Object;
    typeDesc->name = "Object";
    typeDesc->size = sizeof(T);
    typeDesc->members = {
        {"key", offsetof(T, key), reflect::TypeResolver<decltype(Object::key)>::get()},
        {"value", offsetof(T, value), reflect::TypeResolver<decltype(Object::value)>::get()},
        {"next", offsetof(T, next), reflect::TypeResolver<decltype(Object::next)>::get()},
    };
}

struct Node {
    std::string key;
    int value;
    std::vector<Node> children;

    REFLECT()  // Enable reflection for this type
};

// Define Node's type descriptor
REFLECT_STRUCT_DEFINE(Node, key, value, children)

int main() {
    Node node = {"apple", 3, {{"banana", 7, {}}, {"cherry", 11, {}}}};
    reflect::TypeDescriptor* nodeDesc = reflect::TypeResolver<Node>::get();
    nodeDesc->dump(&node);

    cout << endl;
    Object object = {"apple", 5,
                     std::make_unique<Object>("banana", 7, std::make_unique<Object>("cherry", 11, nullptr))};
    reflect::TypeDescriptor* objectDesc = reflect::TypeResolver<Object>::get();
    objectDesc->dump(&object);
    return 0;
}
