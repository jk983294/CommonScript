#include <string>
#include <iostream>
#include <memory>

using namespace std;

/**
 * Problem
 * Convert the interface of a class into another interface that clients expect
 * Adapter lets classes work together that couldn't otherwise because of incompatible interfaces.
 */

// Abstract Target
class Muslim {
public:
    virtual ~Muslim() = default;
    virtual void performsMuslimRitual() const = 0;
};
// Concrete Target
class MuslimFemale : public Muslim {
public:
    virtual void performsMuslimRitual() const override {
        std::cout << "Muslim girl performs Muslim ritual." << std::endl;
    }
};
// Abstract Adaptee
class Hindu {
public:
    virtual ~Hindu() = default;
    virtual void performsHinduRitual() const = 0;
};
// Concrete Adaptee
class HinduFemale : public Hindu {
public:
    virtual void performsHinduRitual() const override {
        std::cout << "Hindu girl performs Hindu ritual." << std::endl;
    }
};

class MuslimRitual {
public:
    void carryOutRitual (Muslim* muslim) {
        std::cout << "On with the Muslim rituals!" << std::endl;
        muslim->performsMuslimRitual();
    }
};
// Adapter
class MuslimAdapter : public Muslim {
private:
    Hindu* hindu;
public:
    MuslimAdapter (Hindu* h) : hindu(h) {}
    virtual void performsMuslimRitual() const override {
        hindu->performsHinduRitual();
    }
};

int main() {
    HinduFemale* hinduGirl = new HinduFemale;
    MuslimFemale* muslimGirl = new MuslimFemale;
    MuslimRitual muslimRitual;
//	muslimRitual.carryOutRitual (hinduGirl);                        // Will not compile of course since the parameter must be of type Muslim*.

    MuslimAdapter* adaptedHindu = new MuslimAdapter (hinduGirl);    // hinduGirl has adapted to become a Muslim!

    muslimRitual.carryOutRitual (muslimGirl);
    muslimRitual.carryOutRitual (adaptedHindu);                     // So now hinduGirl, in the form of adaptedHindu, participates in the muslimRitual!
                                                                    // Note that hinduGirl is carrying out her own type of ritual in muslimRitual though.

    delete adaptedHindu;
    delete hinduGirl;
    delete muslimGirl;
    return 0;
}