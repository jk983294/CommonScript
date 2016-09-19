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

//string��Ĺ��캯����
//
//string(const char *s);    //��c�ַ���s��ʼ��
//string(int n,char c);     //��n���ַ�c��ʼ��
//���⣬string�໹֧��Ĭ�Ϲ��캯���͸��ƹ��캯������string s1��string s2="hello"��������ȷ��д����
//�������string̫�����޷����ʱ���׳�length_error�쳣��
//
//
//string����ַ�������
//const char &operator[](int n)const;
//const char &at(int n)const;
//char &operator[](int n);
//char &at(int n);
//operator[]��at()�����ص�ǰ�ַ����е�n���ַ���λ�ã���at�����ṩ��Χ��飬��Խ��ʱ���׳�out_of_range�쳣���±������[]���ṩ�����ʡ�
//const char *data()const;//����һ����null��ֹ��c�ַ�����
//const char *c_str()const;//����һ����null��ֹ��c�ַ���
//int copy(char *s, int n, int pos = 0) const;//�ѵ�ǰ������pos��ʼ��n���ַ���������sΪ��ʼλ�õ��ַ������У�����ʵ�ʿ�������Ŀ
//
//
//string����������:
//int capacity()const;    //���ص�ǰ��������string�в��������ڴ漴�ɴ�ŵ�Ԫ�ظ�����
//int max_size()const;    //����string�����пɴ�ŵ�����ַ����ĳ���
//int size()const;        //���ص�ǰ�ַ����Ĵ�С
//int length()const;       //���ص�ǰ�ַ����ĳ���
//bool empty()const;        //��ǰ�ַ����Ƿ�Ϊ��
//void resize(int len,char c);//���ַ�����ǰ��С��Ϊlen�������ַ�c��䲻��Ĳ���
//
//string��������������:
//string�����������operator>>�������룬ͬ�����������operator<<�������������
//����getline(istream &in,string &s);���ڴ�������in�ж�ȡ�ַ�����s�У��Ի��з�'\n'�ֿ���
//
//string�ĸ�ֵ��
//string &operator=(const string &s);//���ַ���s������ǰ�ַ���
//string &assign(const char *s);//��c�����ַ���s��ֵ
//string &assign(const char *s,int n);//��c�ַ���s��ʼ��n���ַ���ֵ
//string &assign(const string &s);//���ַ���s������ǰ�ַ���
//string &assign(int n,char c);//��n���ַ�c��ֵ����ǰ�ַ���
//string &assign(const string &s,int start,int n);//���ַ���s�д�start��ʼ��n���ַ�������ǰ�ַ���
//string &assign(const_iterator first,const_itertor last);//��first��last������֮��Ĳ��ָ����ַ���
//
//string�����ӣ�
//string &operator+=(const string &s);//���ַ���s���ӵ���ǰ�ַ����Ľ�β
//string &append(const char *s);            //��c�����ַ���s���ӵ���ǰ�ַ�����β
//string &append(const char *s,int n);//��c�����ַ���s��ǰn���ַ����ӵ���ǰ�ַ�����β
//string &append(const string &s);    //ͬoperator+=()
//string &append(const string &s,int pos,int n);//���ַ���s�д�pos��ʼ��n���ַ����ӵ���ǰ�ַ����Ľ�β
//string &append(int n,char c);        //�ڵ�ǰ�ַ�����β���n���ַ�c
//string &append(const_iterator first,const_iterator last);//�ѵ�����first��last֮��Ĳ������ӵ���ǰ�ַ����Ľ�β
//
//
//string�ıȽϣ�
//bool operator==(const string &s1,const string &s2)const;//�Ƚ������ַ����Ƿ����
//�����">","<",">=","<=","!="�������������ַ����ıȽϣ�
//int compare(const string &s) const;//�Ƚϵ�ǰ�ַ�����s�Ĵ�С
//int compare(int pos, int n,const string &s)const;//�Ƚϵ�ǰ�ַ�����pos��ʼ��n���ַ���ɵ��ַ�����s�Ĵ�С
//int compare(int pos, int n,const string &s,int pos2,int n2)const;//�Ƚϵ�ǰ�ַ�����pos��ʼ��n���ַ���ɵ��ַ�����s��
//
//��������������������������������������������������������������������//pos2��ʼ��n2���ַ���ɵ��ַ����Ĵ�С
//int compare(const char *s) const;
//int compare(int pos, int n,const char *s) const;
//int compare(int pos, int n,const char *s, int pos2) const;
//compare������>ʱ����1��<ʱ����-1��==ʱ����0
//
//
//string���Ӵ���
//string substr(int pos = 0,int n = npos) const;//����pos��ʼ��n���ַ���ɵ��ַ���
//
//string�Ľ�����
//void swap(string &s2);    //������ǰ�ַ�����s2��ֵ
//
//
//string��Ĳ��Һ�����
//int find(char c, int pos = 0) const;//��pos��ʼ�����ַ�c�ڵ�ǰ�ַ�����λ��
//int find(const char *s, int pos = 0) const;//��pos��ʼ�����ַ���s�ڵ�ǰ���е�λ��
//int find(const char *s, int pos, int n) const;//��pos��ʼ�����ַ���s��ǰn���ַ��ڵ�ǰ���е�λ��
//int find(const string &s, int pos = 0) const;//��pos��ʼ�����ַ���s�ڵ�ǰ���е�λ��
////���ҳɹ�ʱ��������λ�ã�ʧ�ܷ���string::npos��ֵ
//int rfind(char c, int pos = npos) const;//��pos��ʼ�Ӻ���ǰ�����ַ�c�ڵ�ǰ���е�λ��
//int rfind(const char *s, int pos = npos) const;
//int rfind(const char *s, int pos, int n = npos) const;
//int rfind(const string &s,int pos = npos) const;
////��pos��ʼ�Ӻ���ǰ�����ַ���s��ǰn���ַ���ɵ��ַ����ڵ�ǰ���е�λ�ã��ɹ���������λ�ã�ʧ��ʱ����string::npos��ֵ
//int find_first_of(char c, int pos = 0) const;//��pos��ʼ�����ַ�c��һ�γ��ֵ�λ��
//int find_first_of(const char *s, int pos = 0) const;
//int find_first_of(const char *s, int pos, int n) const;
//int find_first_of(const string &s,int pos = 0) const;
////��pos��ʼ���ҵ�ǰ���е�һ����s��ǰn���ַ���ɵ���������ַ���λ�á�����ʧ�ܷ���string::npos
//int find_first_not_of(char c, int pos = 0) const;
//int find_first_not_of(const char *s, int pos = 0) const;
//int find_first_not_of(const char *s, int pos,int n) const;
//int find_first_not_of(const string &s,int pos = 0) const;
////�ӵ�ǰ���в��ҵ�һ�����ڴ�s�е��ַ����ֵ�λ�ã�ʧ�ܷ���string::npos
//int find_last_of(char c, int pos = npos) const;
//int find_last_of(const char *s, int pos = npos) const;
//int find_last_of(const char *s, int pos, int n = npos) const;
//int find_last_of(const string &s,int pos = npos) const;
//int find_last_not_of(char c, int pos = npos) const;
//int find_last_not_of(const char *s, int pos = npos) const;
//int find_last_not_of(const char *s, int pos, int n) const;
//int find_last_not_of(const string &s,int pos = npos) const;
////find_last_of��find_last_not_of��find_first_of��find_first_not_of���ƣ�ֻ�����ǴӺ���ǰ����
//
//
//string����滻������
//string &replace(int p0, int n0,const char *s);//ɾ����p0��ʼ��n0���ַ���Ȼ����p0�����봮s
//string &replace(int p0, int n0,const char *s, int n);//ɾ��p0��ʼ��n0���ַ���Ȼ����p0�������ַ���s��ǰn���ַ�
//string &replace(int p0, int n0,const string &s);//ɾ����p0��ʼ��n0���ַ���Ȼ����p0�����봮s
//string &replace(int p0, int n0,const string &s, int pos, int n);//ɾ��p0��ʼ��n0���ַ���Ȼ����p0�����봮s�д�pos��ʼ��n���ַ�
//string &replace(int p0, int n0,int n, char c);//ɾ��p0��ʼ��n0���ַ���Ȼ����p0������n���ַ�c
//string &replace(iterator first0, iterator last0,const char *s);//��[first0��last0��֮��Ĳ����滻Ϊ�ַ���s
//string &replace(iterator first0, iterator last0,const char *s, int n);//��[first0��last0��֮��Ĳ����滻Ϊs��ǰn���ַ�
//string &replace(iterator first0, iterator last0,const string &s);//��[first0��last0��֮��Ĳ����滻Ϊ��s
//string &replace(iterator first0, iterator last0,int n, char c);//��[first0��last0��֮��Ĳ����滻Ϊn���ַ�c
//string &replace(iterator first0, iterator last0,const_iterator first, const_iterator last);//��[first0��last0��֮��Ĳ����滻��[first��last��֮����ַ���
//
//
//string��Ĳ��뺯����
//string &insert(int p0, const char *s);
//string &insert(int p0, const char *s, int n);
//string &insert(int p0,const string &s);
//string &insert(int p0,const string &s, int pos, int n);
////ǰ4��������p0λ�ò����ַ���s��pos��ʼ��ǰn���ַ�
//string &insert(int p0, int n, char c);//�˺�����p0������n���ַ�c
//iterator insert(iterator it, char c);//��it�������ַ�c�����ز�����������λ��
//void insert(iterator it, const_iterator first, const_iterator last);//��it������[first��last��֮����ַ�
//void insert(iterator it, int n, char c);//��it������n���ַ�c
//
//
//string���ɾ������
//iterator erase(iterator first, iterator last);//ɾ��[first��last��֮��������ַ�������ɾ�����������λ��
//iterator erase(iterator it);//ɾ��itָ����ַ�������ɾ�����������λ��
//string &erase(int pos = 0, int n = npos);//ɾ��pos��ʼ��n���ַ��������޸ĺ���ַ���
//
//
//string��ĵ���������
//string���ṩ����ǰ���������ĵ�����iterator���������ṩ�˷��ʸ����ַ����﷨��������ָ�����������������鷶Χ��
//��string::iterator��string::const_iterator����������������const_iterator������ı���������ݡ����õ����������У�
//const_iterator begin()const;
//iterator begin();                //����string����ʼλ��
//const_iterator end()const;
//iterator end();                    //����string�����һ���ַ������λ��
//const_iterator rbegin()const;
//iterator rbegin();                //����string�����һ���ַ���λ��
//const_iterator rend()const;
//iterator rend();                    //����string��һ���ַ�λ�õ�ǰ��
//rbegin��rend���ڴӺ���ǰ�ĵ������ʣ�ͨ�����õ�����string::reverse_iterator,string::const_reverse_iteratorʵ��
//
//
//�ַ���������
//ͨ������ostringstream��istringstream����ʵ�֣�#include <sstream>ͷ�ļ���
//���磺
//string input("hello,this is a test");
//istringstream is(input);
//string s1,s2,s3,s4;
//is>>s1>>s2>>s3>>s4;//s1="hello,this",s2="is",s3="a",s4="test"
//ostringstream os;
//os<<s1<<s2<<s3<<s4;
//cout<<os.str();