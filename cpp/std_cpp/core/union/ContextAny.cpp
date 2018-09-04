#include <cstring>
#include <iostream>
#include <string>

using namespace std;

enum ContextTypeIndex : uint8_t {
    char_type,
    string_type,
    char_array_type,
    int_type,
    long_type,
    float_type,
    double_type
};

struct ContextAny {
    union AnyContent {
        char CHAR;
        int INT32;
        long INT64;
        float FLOAT32;
        double FLOAT64;
        char* CharArray;
        std::string STRING;
        ~AnyContent() {}
        AnyContent() {}
    };

    ContextTypeIndex type;
    AnyContent data;

    char& get_char() { return data.CHAR; }
    int& get_int() { return data.INT32; }
    long& get_long() { return data.INT64; }
    float& get_float() { return data.FLOAT32; }
    double& get_double() { return data.FLOAT64; }
    std::string& get_string() { return data.STRING; }
    char*& get_char_array() { return data.CharArray; }

    ContextAny() {}

    ContextAny(int value) {
        data.INT32 = value;
        type = ContextTypeIndex::int_type;
    }
    ContextAny(long value) {
        data.INT64 = value;
        type = ContextTypeIndex::long_type;
    }
    ContextAny(float value) {
        data.FLOAT32 = value;
        type = ContextTypeIndex::float_type;
    }
    ContextAny(double value) {
        data.FLOAT64 = value;
        type = ContextTypeIndex::double_type;
    }
    ContextAny(const std::string& value) {
        new (&data.STRING) std::string(value);
        type = ContextTypeIndex::string_type;
    }
    ContextAny(char* value) {
        data.CharArray = value;
        type = ContextTypeIndex::char_array_type;
    }
    ContextAny(const char* value) {
        data.CharArray = const_cast<char*>(value);
        type = ContextTypeIndex::char_array_type;
    }

    ContextAny(const ContextAny& rhs) : type(rhs.type) {
        switch (rhs.type) {
            case ContextTypeIndex::string_type:
                new (&data.STRING) std::string(rhs.data.STRING);
                break;
            default:
                std::memcpy(&data, &rhs.data, sizeof(data));
        }
    }

    ~ContextAny() {
        if (type == ContextTypeIndex::string_type) data.STRING.~basic_string();
    }
};

int main() {
    cout << sizeof(std::string) << endl;
    string str{"hello"};
    ContextAny any(str);
    cout << any.get_string() << endl;
    ContextAny any1 = any;
    cout << any1.get_string() << endl;
    ContextAny any2(1);
    ContextAny any3(any2);
    cout << any3.get_int() << endl;
    ContextAny any4(any);
    cout << any4.get_string() << endl;
    ContextAny any5;
    return 0;
}
