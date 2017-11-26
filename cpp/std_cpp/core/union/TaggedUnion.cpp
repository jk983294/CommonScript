#include <cstring>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Value {  // two alternative representations represented as a union
private:
    enum class Tag { number, text };
    Tag type;  // discriminant

    union {  // representation (note: anonymous union)
        int i;
        string s;  // string has default constructor, copy operations, and destructor
    };

public:
    struct Bad_entry {};  // used for exceptions

    Value(int a) : type(Tag::number), i(a) {}
    Value(const string& a) : type(Tag::text), s(a) {}
    ~Value();
    Value& operator=(const Value&);  // necessary because of the string variant
    Value(const Value&);
    int number() const;
    string text() const;

    void set_number(int n);
    void set_text(const string&);
};

int Value::number() const {
    if (type != Tag::number) throw Bad_entry{};
    return i;
}

string Value::text() const {
    if (type != Tag::text) throw Bad_entry{};
    return s;
}

void Value::set_number(int n) {
    if (type == Tag::text) {
        s.~string();  // explicitly destroy string
        type = Tag::number;
    }
    i = n;
}

void Value::set_text(const string& ss) {
    if (type == Tag::text)
        s = ss;
    else {
        new (&s) string{ss};  // placement new: explicitly construct string
        type = Tag::text;
    }
}

Value& Value::operator=(const Value& e)  // necessary because of the string variant
{
    if (type == Tag::text && e.type == Tag::text) {
        s = e.s;  // usual string assignment
        return *this;
    }

    if (type == Tag::text) s.~string();  // explicit destroy

    switch (e.type) {
        case Tag::number:
            i = e.i;
            break;
        case Tag::text:
            new (&s) string{e.s};  // placement new: explicit construct
            type = e.type;
    }

    return *this;
}

Value::~Value() {
    if (type == Tag::text) s.~string();  // explicit destroy
}

int main() {
    Value v(0);
    v.set_number(42);
    cout << v.number() << endl;
    v.set_text("24");
    cout << v.text() << endl;
    return 0;
}
