#include <iostream>
#include <string>
#include <vector>
#include <boost/signals2.hpp>

using namespace std;
using namespace boost;
using namespace boost::signals2;

class Player
{
public:
    string name;
    int numberOfGoals;
    Player(string name) : name(name), numberOfGoals(0) {}
    signal<void(string, int)> scores;

    void score()
    {
        numberOfGoals++;
        scores(name, numberOfGoals);
    }
};
/**
 * signal 2 slot, publisher and subscriber
 */
int main(int argc, char *argv[])
{
    Player p("jk");

    auto c = p.scores.connect([](string name, int count){
        cout << "player " << name << " has scored " << count << "goals already" << endl;
    });


    p.score();
    p.score();

    {   // temporary block the event emit
        shared_connection_block b(c);
        p.score();
        p.score();
    }

    p.score();
    p.score();

    p.scores.disconnect_all_slots();

    p.score();
    p.score();

    getchar();
    return 0;
}