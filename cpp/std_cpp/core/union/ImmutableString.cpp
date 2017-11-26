#include <cstring>
#include <iostream>
#include <string>

using namespace std;

/**
 * short-string optimization
 */

constexpr size_t buffer_size = 16;  // Slightly larger than the size of a pointer

class ImmutableString {
public:
    ImmutableString(const char* str) : size(strlen(str)) {
        if (size < buffer_size)
            strcpy(string_buffer, str);
        else {
            string_ptr = new char[size + 1];
            strcpy(string_ptr, str);
        }
    }

    ~ImmutableString() {
        if (size >= buffer_size) delete string_ptr;
    }

    const char* get_str() const { return (size < buffer_size) ? string_buffer : string_ptr; }

private:
    // If the string is short enough, we store the string itself
    // instead of a pointer to the string.
    union {
        char* string_ptr;
        char string_buffer[buffer_size];
    };

    const size_t size;
};

int main() {
    ImmutableString str1("hello");
    ImmutableString str2("world");
    ImmutableString str3("hello world, this is a very very long sentence.");

    cout << str1.get_str() << endl;
    cout << str2.get_str() << endl;
    cout << str3.get_str() << endl;
    return 0;
}
