#include <any>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <tuple>

namespace pt = boost::property_tree;
using namespace std;

void process(const pt::ptree& config);

int main() {
    pt::ptree root;
    pt::read_json("../test.json", root);
    int height = root.get<int>("height", 0);
    std::string msg = root.get<std::string>("some.complex.path");  // go through nested nodes
    cout << height << " " << msg << endl;

    // go through attributes
    std::vector< std::pair<std::string, std::string> > animals;
    for (pt::ptree::value_type &animal : root.get_child("animals")) {
        std::string name = animal.first;
        std::string color = animal.second.data();
        animals.push_back(std::make_pair(name, color));
    }
    cout << "animals size " << animals.size() << endl;

    // go through array
    std::vector<std::string> fruits;
    for (pt::ptree::value_type &fruit : root.get_child("fruits")) {
        fruits.push_back(fruit.second.get_value<std::string>());
        // fruits.push_back(fruit.second.data());
    }
    cout << "fruits size " << animals.size() << endl;

    auto y_def_node = root.get_child_optional("y_def");
    if (y_def_node) {
        bool a = y_def_node->get<bool>("y_consider_exclude", false);
        bool b = y_def_node->get<bool>("y_consider_tradable", false);
        auto itvls_node = y_def_node->get_child_optional("intervals");
        if (itvls_node) {
            for (pt::ptree::value_type &row : *itvls_node) {
                std::string itvl;
                std::string skip;
                for (pt::ptree::value_type &cell : row.second) {
                    std::string name = cell.first;
                    std::string value = cell.second.data();
                    if (name == "value") itvl = value;
                    else if (name == "skip") skip = value;
                }
                printf("%d,%d,%s,%s\n", a, b, itvl.c_str(), skip.c_str());
            }
        }
    }

    // matrices
    int matrix[3][3];
    int xIdx = 0;
    for (pt::ptree::value_type &row : root.get_child("matrix")) {
        int yIdx = 0;
        for (pt::ptree::value_type &cell : row.second) {
            matrix[xIdx][yIdx] = cell.second.get_value<int>();
            yIdx++;
        }
        xIdx++;
    }
    cout << "matrix " << matrix[2][2] << endl;

    // read mix attr
    std::unordered_map<string, string> attrs;
    auto node = root.get_child_optional("mix_attr");
    if (node) {
        process(*node);
        for (auto& item : *node) {
            attrs[item.first] = item.second.data();
        }
    }
    cout << "attrs " << attrs.size() << endl;
}

void process(const pt::ptree& config) {
    for (auto& item : config) {
        cout << item.first << endl;
        cout << item.second.data() << endl;
    }
}