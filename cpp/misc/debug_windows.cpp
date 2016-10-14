#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <crtdbg.h>

/**
 * debug utility
 * assert, only run for debug mode
 * verify, assert for debug mode, run expression for release mode
 * trace, output something for debug mode, output nothing for release mode
 */

struct Tracer
{
    const char* file_name;
    unsigned int line;
    Tracer(const char* _file_name, const unsigned int _line): file_name(_file_name), line(_line){}
    void operator()(const std::string msg) const {
        std::cout << file_name << "(" << line << "): " << msg << std::endl;
    }
};

#ifdef _DEBUG
inline auto Trace(const std::string msg) -> void {
	std::cout << msg << std::endl;
}
#endif

#ifdef _DEBUG
#define VERIFY _ASSERTE
#define TRACE Tracer(__FILE__, __LINE__)
#else
#define VERIFY(expression) (expression)
#define TRACE __noop
#endif

auto main() -> int {
    VERIFY(std::cout << "verify test" << std::endl);
    TRACE("trace test");
    static_assert( sizeof(float) == 4, "cannot handle this kind of floats!");
    _ASSERTE(4 == 5);			// for GUI application popup, windows specific
    assert(4 == 5);				// for cmd application
}













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














#include <iostream>
#include <unordered_map>

using namespace std;


/**
 * unordered associative container use hash structure, so it doesn't maintain the order of elements
 * unordered_map, unordered_set, unordered_multimap, unordered_multiset
 * unordered associative container use tree structure, so it does maintain the order of elements
 * map, set, multimap, multiset
 */

struct Hen
{
	int x;
	int y;
	Hen(int x_, int y_): x { x_}, y {y_} {}
};

bool operator==(const Hen& left, const Hen& right) {
	return left.x == right.x && left.y == right.y;
}

namespace std {
	template <>
	struct hash<Hen>
	{
		size_t operator()(const Hen& hen) const {
			return hash<int>{} (hen.x) ^ hash<int>{} (hen.y);
		}
	};
}

int main() {
	auto c1 = unordered_map<int, double, hash<int>, equal_to<int> > {};

	auto c = unordered_map<Hen, double> {
		{ { 1, 2 }, 1.1 },
		{ { 2, 3 }, 2.1 },
		{ { 3, 4 }, 3.1 },
		{ { 4, 5 }, 4.1 },
	};

	c[{5, 6}] = 5.1;

	auto k = Hen { 6, 7 };
	c[k] = 6.1;

	c.emplace( Hen { 7, 8 }, 7.1);

	for (auto & v : c){
		cout << v.first.x << " " << v.first.y << " " << v.second << endl;
	}
    return 0;
}














#include <iostream>
#include <string>

using namespace std;


/**
 * basic_string container, string is just a typedef specilized basic_string container
 */

string trim(const string& s){
	auto front = find_if_not(begin(s), end(s), isspace);
	auto back = find_if_not(rbegin(s), rend(s), isspace);
	return string { front, back.base() };
}


int main() {
	string s = string {};
	s = basic_string<char> {};
	wstring ws = wstring {};
	ws = basic_string<wchar_t> {};

	s = string { "kun" };
	cout << "size " << s.size() << endl;
	cout << "content " << s.c_str() << endl;

	s.clear();
	cout << "size " << s.size() << endl;
	cout << "empty " << s.empty() << endl;
	cout << "empty " << (strcmp(s.c_str(), "")) << endl;

	s = string { "get sub string" };
	auto sub = string (s, 4, 3);
	cout << "sub string: " << sub << endl;

	auto pos = s.find("sub");
	sub = s.substr(pos);
	cout << "sub string: " << sub << endl;

	auto trimed = trim("  \t kun jiang \n \n");
	cout << "trimed: " << trimed << endl;
    return 0;
}




#include <iostream>
#include <string>
#include <regex>

using namespace std;


/**
 * regular expression
 */


int main() {
	string s = string("call 110-110-110 to police!");
	auto r = reg( R"((\d{3})-(\d{3})-(\d{3}))" );
	auto m = smatch {};			// cmatch{}
	cout << "empty " << m.empty() << endl;
	regex_search(s, m, r);
	cout << "empty " << m.empty() << endl;
	for (auto & sub : m){
		auto str = sub.str();
		cout << sub.length() << " " << &*sub.first << endl;
	}

	auto output = m.format();
	cout << "output " << output << endl;
    return 0;
}
