#include <iostream>
#include <vector>

using namespace std;

/**
* type rich programming
* using template and suffix literal operator overloading
* dimension analysis
* length, mass, time (m, Kg, s)
*/

template<int M, int K, int S>
struct Unit {
    static const int m = M;
    static const int k = K;
    static const int s = S;
};

template< typename UNIT>
struct Value {
    //the raw naked value
    double val;
    //retain access to unit's values after first stage compilation
    static constexpr int getM(){ return UNIT::m; }
    static constexpr int getK(){ return UNIT::k; }
    static constexpr int getS(){ return UNIT::s; }

    //constructors
    explicit Value(double d): val(d){}
    constexpr Value(): val(0){}

    void print(){
        cout << "<" << UNIT::m << ", " << UNIT::k << ", " << UNIT::s << ">" << endl;
        cout << val << endl;
    }

    Value<UNIT> add(Value<UNIT>& another){
        return Value<UNIT>(val + another.val);
    }

    Value<UNIT> operator +(const Value<UNIT>& another ){
        return Value<UNIT>(val + another.val);
    }

    template< typename OTHER >
    Value<Unit<getM()-OTHER::getM(), getK()-OTHER::getK(), getS()-OTHER::getS()>>
    operator /
    (const OTHER& other){
        Value<Unit<getM()-other.getM(), getK()-other.getK(), getS()-other.getS()>> result(val / other.val);
        return result;
    }
};

using second = Unit<0,0,1>;
using second2 = Unit<0,0,2>;
using meter = Unit<1,0,0>;
using Speed = Value<Unit<1,0,-1>>;
using Distance = Value<meter>;
using Acceleration = Value<Unit<1,0,-2>>;	//global scope

Value<second> operator"" _s (long double d){
    return Value<second>(d);
};
Value<meter> operator"" _m (long double d){
    return Value<meter>(d);
};
Value<meter> operator"" _m (unsigned long long d){
    return Value<meter>(d);
};
Value<second2> operator"" _s2 (long double d){	//overloaded second square suffix operator
    return Value<second2>(d);
};



int main(){
    Speed spd = 1_m / 3.3_s;
    Acceleration acc1 = 1.0_m/2.4_s2;
    Acceleration acc2 = 4.8_m/2.1_s2;
    Acceleration acc3 = acc1 + acc2;
    Acceleration acc = 8.0_m/3.3_s2;
    return 0;
}
