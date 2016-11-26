#include <iostream>
#include <string>
#include <vector>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>

using namespace std;
using namespace boost;
using namespace boost::signals2;

class Player
{
public:
    string name;
    int numberOfGoals;
    Player(string name) : name(name), numberOfGoals(0) {}
    typedef signal<void(string, int)> SignalType;
    SignalType scores;

    void score()
    {
        numberOfGoals++;
        scores(name, numberOfGoals);
    }
};

class Coach
{
public:
    void playerScored(string name){
        cout << "well done, " << name << endl;
    }
};

int main(int argc, char *argv[])
{
    Coach* coach = new Coach;
    Player p("jk1");

    {
        auto coach = boost::make_shared<Coach>();
        p.scores.connect(
            Player::SignalType::slot_type
            (&Coach::playerScored, coach.get(), _1).track(coach)
            );
        p.score();
    }

    p.score();          // track detect the object is deleted, so it won't signal again

    getchar();
    return 0;
}