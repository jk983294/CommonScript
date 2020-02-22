#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

struct Object {
    int a1;
    float a2;
    double a3;
    char a4[8];
};

struct DataField {
    char data_tag[100];
    int data_type;  // type of RAW data: 0-double 1-int 2-char[data_len] 3-float
    int offset;
    size_t data_len;

    DataField(int type, int offset_, const char *name, size_t size) {
        data_type = type;
        offset = offset_;
        data_len = size;
        strcpy(data_tag, name);
    }
};

#define __DataField(data_type, name, class_type, field) \
    DataField { data_type, offsetof(class_type, field), name, sizeof(class_type::field) }

int main() {
    vector<DataField> v;
    v.emplace_back(__DataField(1, "a1", Object, a1));
    v.emplace_back(__DataField(3, "a2", Object, a2));
    v.emplace_back(__DataField(0, "a3", Object, a3));
    v.emplace_back(__DataField(2, "a4", Object, a4));

    Object obj;
    obj.a1 = 1;
    obj.a2 = 2;
    obj.a3 = 3;
    strcpy(obj.a4, "4");

    for (auto &field : v) {
        cout << field.data_tag << "," << field.data_type << "," << field.offset << "," << field.data_len << endl;

        char *dp = ((char *)&obj) + field.offset;
        if (field.data_type == 0) {
            cout << "double " << *(double *)dp << endl;
        } else if (field.data_type == 1) {
            cout << "int " << *(int *)dp << endl;
        } else if (field.data_type == 2) {
            cout << "char* " << *dp << endl;
        } else if (field.data_type == 3) {
            cout << "float " << *(float *)dp << endl;
        }
    }

    return 0;
}
