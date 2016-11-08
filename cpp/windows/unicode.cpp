#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

class TCHARHelper
{
public:
    TCHARHelper(void) : m_pastr(NULL), m_pwstr(NULL), m_localpage(936){}
    ~TCHARHelper(void){
        if (m_pwstr != NULL){
            delete[] m_pwstr;
            m_pwstr = NULL;
        }

        if (m_pastr != NULL){
            delete[] m_pastr;
            m_pastr = NULL;
        }
    }

    char* TCHAR2char(TCHAR* pstr){
        #ifdef UNICODE
            return wchar_t2char(pstr);
        #else
            return pstr;
        #endif
    }

    wchar_t* TCHAR2wchar_t(TCHAR* pstr){
        #ifdef UNICODE
            return pstr;
        #else
            return char2wchar_t(pstr);
        #endif
    }

    TCHAR* char2TCHAR(char* pstr){
        #ifdef UNICODE
            return char2wchar_t(pstr);
        #else
            return pstr;
        #endif
    }

    TCHAR* wchar_t2TCHAR(wchar_t* pstr){
        #ifdef UNICODE
            return pstr;
        #else
            return char2wchar_t(pstr);
        #endif
    }

    //set local charset
    void SetLocalPage(int localpage){
        m_localpage = localpage;
    }

private:
    char* wchar_t2char(wchar_t* pstr){
        if (pstr == NULL){
            return NULL;
        }

        int needlen = WideCharToMultiByte(m_localpage, 0, pstr, -1, 0, 0, NULL, NULL);
        if (needlen <= 0){
            return NULL;
        }

        if (m_pastr != NULL){
            delete m_pastr;
            m_pastr = NULL;
        }
        m_pastr = new char[needlen];

        if (WideCharToMultiByte(m_localpage, 0, pstr, -1, m_pastr, needlen, NULL, NULL) != needlen){
            return NULL;
        }

        return m_pastr;
    }
    wchar_t* char2wchar_t(char* pstr){
        if (pstr == NULL){
            return NULL;
        }

        int needlen = MultiByteToWideChar(m_localpage, 0, pstr, -1, 0, 0);

        if (m_pwstr != NULL){
            delete[] m_pwstr;
            m_pwstr = NULL;
        }
        m_pwstr = new wchar_t[needlen];

        if (MultiByteToWideChar(m_localpage, 0, pstr, -1, m_pwstr, needlen) != needlen){
            return NULL;
        }

        return m_pwstr;
    }

private:
    char* m_pastr;
    wchar_t* m_pwstr;
    int m_localpage;
};

int main(){
    cout << "hello world" << endl;          // ascii string
    cout << L"hello world" << endl;         // unicode string

    char name[10];                          // ascii
    wchar_t name1[10];                      // unicode
    TCHAR name2[10];                        // depends on compile charset setting, _UNICODE macro
    
    return 0;
}