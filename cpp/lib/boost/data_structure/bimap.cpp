#include <iostream>
#include <string>
#include <boost/bimap.hpp>
using namespace std;
using namespace boost;

enum class Color
{
    Red,
    Green,
    Blue
};

typedef bimap<Color, string> ColorMapType;
ColorMapType colorTypes;

int main(int argc, char *argv[])
{
    colorTypes.insert(ColorMapType::value_type(Color::Red, "Red"));
    colorTypes.insert(ColorMapType::value_type(Color::Green, "Green"));
    colorTypes.insert(ColorMapType::value_type(Color::Blue, "Blue"));

    Color c = colorTypes.right.at("Red");

    string s = colorTypes.left.at(Color::Red);

    cout << s << endl;

    getchar();
    return 0;
}