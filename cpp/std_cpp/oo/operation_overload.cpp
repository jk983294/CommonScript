#include <iostream>

using namespace std;


/**
 * unary                                member
 * = () [] ->                           must member
 * += -= /= *= ^= &= != %= >>= <<=      member
 * binary                               non-member
 */

class Number {
public:
    constexpr Number(): data(0){};
    constexpr explicit Number(int i): data(i){};
    /**
     * here copy constructor and assign operator is useless
     * it is useful for those class contains dynamic data
     * deep copy and release resource correctly
     */
    constexpr Number(const Number& i): data(i.data){};
    Number& operator=(const Number& i){
        if (this != &i){
            data = i.data;
        }
        return *this;
    };
    /**
     * move constructor, like lvalue reference but can bind to temporaries
     * steal data from temporaries (like pointer), cheap than copy constructor
     */
    constexpr Number(Number&& i): data(i.data){};
    Number& operator=(Number&& i){
        if (this != &i){
            data = i.data;
        }
        return *this;
    };

    /**
     * function call overload
     */
    void operator()(int x){
        cout << "call void operator()(int x)" << endl;
    }
    void operator()(int x, int y){
        cout << "call void operator()(int x, int y)" << endl;
    }

    int operator[] (int i){
        int x = data;
        while(i > 0){
            x /= 10;
            --i;
        }
        return x % 10;
    }

    /**
     * conversion operator, convert object to other type
     */
    operator int () const { return data; }

    /**
     * ++(++i);
     * i++;
     */
    Number& operator++(){ ++data; }         // prefix ++
    Number operator++(int){                 // postfix ++
        Number temp = *this;
        ++data;
        return temp;
    }
    /**
     * return const in case (a * b) = c;
     */
    friend const Number operator+(const Number& l, const Number& r);
    friend const Number operator-(const Number& l, const Number& r);
    friend const Number operator*(const Number& l, const Number& r);
    friend const Number operator/(const Number& l, const Number& r);

    friend bool operator<(const Number& left, const Number& right);
    friend bool operator>(const Number& left, const Number& right);
    friend bool operator<=(const Number& left, const Number& right);
    friend bool operator>=(const Number& left, const Number& right);
    friend bool operator==(const Number& left, const Number& right);
    friend bool operator!=(const Number& left, const Number& right);

    friend ostream& operator<<(ostream& s, const Number);
    friend istream& operator>>(istream& s, Number&);
    /**
     * cannot overload . .* :: ?:
     */
public:
    int data;
};
ostream& operator<<(ostream& s, const Number n){
    s << "Number [" << n.data << "]";
    return s;
}
istream& operator>>(istream& is, Number& n){
    is >> n.data;
    return is;
}
const Number operator+(const Number& l, const Number& r){
    return Number(l.data + r.data);
}
const Number operator-(const Number& l, const Number& r){
    return Number(l.data - r.data);
}
const Number operator*(const Number& l, const Number& r){
    return Number(l.data * r.data);
}
const Number operator/(const Number& l, const Number& r){
    return Number(l.data / r.data);
}
bool operator<(const Number& left, const Number& right){
    return left.data < right.data;
}
bool operator>(const Number& left, const Number& right){
    return left.data > right.data;
}
bool operator==(const Number& left, const Number& right){
    return left.data == right.data;
}
bool operator<=(const Number& left, const Number& right){
    return left.data <= right.data;
}
bool operator>=(const Number& left, const Number& right){
    return left.data >= right.data;
}
bool operator!=(const Number& left, const Number& right){
    return left.data != right.data;
}
int main() {
    Number n(3);
    Number n1(15);
    Number n2  = n * n1;
    // n = 5;                                           // failed due to explicit int constructor
    cout << n << endl;
    cout << n2 << endl;
    cout << n1[1] << " " << n1[0] << endl;
    n1(1);
    n1(1, 2);
    return 0;
}