#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>

using namespace std;

/**
 * Problem
 * the pattern ensures that a class has only one instance and provides a global point of access to that instance.
 */

class StringSingleton
{
public:
    std::string getString() const
    {
        return mString;
    }
    void setString(const std::string &newStr)
    {
        mString = newStr;
    }

    // lazy initialization, C++11 does guarantee that this is thread-safe
    static StringSingleton& instance()
    {
        static StringSingleton *instance = new StringSingleton;
        // return reference to removes temptation to try and delete the returned instance.
        return *instance;
    }

private:
    StringSingleton(){}

    // this prevents accidental copying of the only instance of the class.
    StringSingleton(const StringSingleton &old);
    const StringSingleton &operator=(const StringSingleton &old);

    // This prevents others from deleting our one single instance, which was otherwise created on the heap
    ~StringSingleton(){}
private:
    std::string mString;
};

int main()
{
    StringSingleton::instance().getString();

    return 0;
}