#include <iostream>
#include <string>
#include <ctime>
#include <boost/signals2.hpp>

using namespace std;
using namespace boost;
using namespace boost::signals2;

template <typename T> class INotifyPropertyChanged
{
public:
    signal<void(const T*, string)> propertyChanged;
};

class Player : public INotifyPropertyChanged<Player>
{
public:
    Player(string name) : name(name), age(0) {}
    ~Player(){}
    void setAge(int value)
    {
        if (value == age) return;
        age = value;
        propertyChanged(this, "Age");
    }
    int getAge() const
    {
        return age;
    }

    string name;
private:
    int age;
};

int main(int argc, char *argv[])
{
    Player p("jk");

    p.propertyChanged.connect(
        [](const Player* p, string propertyName)
    {
        cout << p->name << " " << propertyName << " has changed to " << p->getAge() << endl;
    });

    p.setAge(10);

    getchar();
    return 0;
}