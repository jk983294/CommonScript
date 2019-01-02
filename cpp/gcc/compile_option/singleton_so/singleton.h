#ifndef BEAUTY_SINGLETON_H
#define BEAUTY_SINGLETON_H

class singleton {
private:
    singleton() { num = -1; }
    static singleton* pInstance;

public:
    static singleton& instance() {
        if (NULL == pInstance) {
            pInstance = new singleton();
        }
        return *pInstance;
    }

public:
    int num;
};

singleton* singleton::pInstance = NULL;

#endif
