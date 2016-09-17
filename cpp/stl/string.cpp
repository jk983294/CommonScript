#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

void init(){
    string s1;
    s1="i love you";
    string s2(s1);
    string s3("value");
    string s4(10,'s');
    cin>>s1;
    getline(cin, s1);           // read until \n
    getline(cin, s1, 'a');      // read until char 'a', any \n is accept
}

void basic_operation(){
    string str2("world");
    string str3="hello ";
    str3 += str2;
    str3.append("!!!");
    cout<<str3<<endl;
    cout<<str3.size()<<endl;
    for(string::size_type i=0; i < str3.size(); ++i) {
        cout<<str3[i];
    }
    cout<<endl;
}

void char_operation(){
    cout<<isalnum('a')<<" "<<isalnum('1')<<endl;
    cout<<isalpha('a')<<" "<<isalpha('1')<<endl;
    cout<<iscntrl('\t')<<" "<<iscntrl('a')<<endl;
    cout<<isdigit('a')<<" "<<isdigit('1')<<endl;
    cout<<isgraph('a')<<" "<<isgraph('1')<<endl;
    cout<<islower('a')<<" "<<islower('A')<<endl;
    cout<<isupper('a')<<" "<<isupper('A')<<endl;
    cout<<isprint('a')<<" "<<isprint('1')<<endl;
    cout<<ispunct(';')<<" "<<ispunct('.')<<endl;
    cout<<isspace(' ')<<" "<<isspace('a')<<endl;
    cout<<isxdigit('a')<<" "<<isxdigit('A')<<endl;
    cout<<tolower('a')<<" "<<tolower('A')<<endl;
    cout<<toupper('a')<<" "<<toupper('A')<<endl;
}

void reverse_string(){
    string s;
    s="54268713";
    reverse(s.begin(),s.end());
    cout<<s<<endl;
}

void crud(){
    string s1="i love you";
    string::iterator it;
    it=s1.begin();
    s1.insert(it+1,'p');
    cout<<s1<<endl;

    string s2("abc123456");
    string::iterator it2 = s2.begin();
    s2.erase(it2 + 6);
    cout<<s2<<endl;
    s2.erase(it2, it2+3);
    cout<<s2<<endl;
    s2.replace(2, 1, "good");
    cout<<s2<<endl;
    cout<<s2.find("good")<<endl;
    cout<<s2.compare("12good55")<<endl;
    cout<<s2.compare("12good56")<<endl;
    cout<<s2.compare("12good56758")<<endl;
}

string number_to_string(double x)  {
    ostringstream o;
    o<<x;
    return o.str();
}
double string_to_number(const string &s){
    istringstream i(s);
    double x;
    i >> x;
    return x;
}


int main() {
    cout<<number_to_string(1.2)<<endl;
    cout<<string_to_number("1.2")<<endl;
    crud();
    reverse_string();
    basic_operation();
    char_operation();
    init();
    return 0;
}