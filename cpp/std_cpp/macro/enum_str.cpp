#include <cstring>
#include <stdexcept>
#include <string>

// https://stackoverflow.com/questions/147267/easy-way-to-use-variables-of-enum-types-as-string-in-c
// expansion macro for enum value definition
#define ENUM_VALUE(name, assign) name assign,

// expansion macro for enum to string conversion
#define ENUM_CASE(name, assign) \
    case name:                  \
        return #name;

// expansion macro for string to enum conversion
#define ENUM_STRCMP(name, assign) \
    if (!strcmp(str, #name)) return name;

/// declare the access function and define enum values in .h
#define DECLARE_ENUM(EnumType, ENUM_DEF)    \
    enum EnumType { ENUM_DEF(ENUM_VALUE) }; \
    const char *type2str(EnumType dummy);   \
    EnumType str2type(const char *str);

/// define the access function names in .cpp
#define DEFINE_ENUM(EnumType, ENUM_DEF)                                                       \
    const char *type2str(EnumType value) {                                                    \
        switch (value) {                                                                      \
            ENUM_DEF(ENUM_CASE)                                                               \
            default:                                                                          \
                return ""; /* handle input error */                                           \
        }                                                                                     \
    }                                                                                         \
    EnumType str2type(const char *str) {                                                      \
        ENUM_DEF(ENUM_STRCMP)                                                                 \
        throw std::runtime_error("invalid enum" + std::string(str)); /* handle input error */ \
        return (EnumType)0;                                                                   \
    }

#define TYPES_LIST(XX)       \
    XX(FirstValue, )         \
    XX(SecondValue, )        \
    XX(SomeOtherValue, = 50) \
    XX(OneMoreValue, = 100)

DECLARE_ENUM(MyTYPES, TYPES_LIST)

DEFINE_ENUM(MyTYPES, TYPES_LIST)

int main() {
    const char *type_str0 = type2str(MyTYPES::FirstValue);
    auto e_type0 = str2type(type_str0);
    std::string type_str1 = "SomeOtherValue";
    auto e_type1 = str2type(type_str1.c_str());
    printf("value=%d,%d\n", e_type0, e_type1);
}