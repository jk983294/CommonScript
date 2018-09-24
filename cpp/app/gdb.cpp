#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

inline std::string &ltrim(std::string &s);
inline std::string &rtrim(std::string &s);
inline std::string &trim(std::string &s);
inline std::vector<std::string> split(const std::string &str);

std::vector<std::string> results{"1", "d", "df", "s", "s"};
std::vector<std::string> userDefinedContext{"var1", "var2", "var3", "var4", "var5"};
std::unordered_map<std::string, size_t> userDefinedVarName2index{
    {"var1", 0}, {"var2", 1}, {"var3", 2}, {"var4", 3}, {"var5", 4}};

void printVariable(const std::string &name) {
    std::cout << "variable: ";
    if (name == "all") {
        for (size_t i = 0; i < results.size(); ++i) {
            std::cout << userDefinedContext[i] << ": " << results[i] << ", ";
        }
    } else {
        if (userDefinedVarName2index.find(name) != userDefinedVarName2index.end()) {
            size_t index = userDefinedVarName2index[name];
            if (index < results.size()) {
                std::cout << userDefinedContext[index] << ": " << results[index];
            } else {
                std::cerr << "something wrong! probably caused by exit abruptly when recording.";
            }
        } else {
            std::cout << "key not found";
        }
    }
}

void printCommand(const std::string &arg1, const std::string &arg2) {
    if (arg1 == "all") {
        std::cout << "all" << std::endl;
        printVariable(arg2);
    } else if (arg1 == "variable") {
        printVariable(arg2);
    } else if (arg1 == "time") {
        std::cout << "time now is xxx" << std::endl;
    }
    std::cout << std::endl;
}

void infoCommand(const std::string &arg1) {
    std::cout << "variable: ";
    for (size_t i = 0; i < results.size(); ++i) {
        std::cout << userDefinedContext[i] << ", ";
    }
    std::cout << std::endl;
}

int main() {
    std::string line;
    std::string lastCmd;
    int round = 0;
    while (true) {
        std::cout << "round " << round << std::endl;
        std::cout << "> ";
        while (std::getline(std::cin, line)) {
            trim(line);
            if (line.empty()) {
                line = lastCmd;
            } else {
                lastCmd = line;
            }

            std::vector<std::string> ret = split(line.c_str());

            if (ret.size() > 0) {
                std::string cmd{ret[0]};
                if (cmd == "help" || cmd == "h") {
                    std::cout << "command\t\t\tusage\t\t\t\t\t\t\t\tdescription\n"
                              << "help,h\t\t\thelp\t\t\t\t\t\t\t\tget usage\n"
                              << "print,p\t\t\tprint (variable|time|all) [name]\tprint out selected variable\n"
                              << "info,i\t\t\tinfo (variable)\t\t\t\t\t\tprint available variable name\n"
                              << "continue,c\t\tcontinue\t\t\t\t\t\t\tcontinue replay" << std::endl;
                } else if (cmd == "print" || cmd == "p") {
                    std::string arg1 = ret.size() > 1 ? ret[1] : "variable";
                    std::string arg2 = ret.size() > 2 ? ret[2] : "all";
                    printCommand(arg1, arg2);
                } else if (cmd == "info" || cmd == "i") {
                    std::string arg1 = ret.size() > 1 ? ret[1] : "variable";
                    infoCommand(arg1);
                } else if (cmd == "continue" || cmd == "c") {
                    break;
                } else {
                    std::cout << "unknown command" << std::endl;
                }
                std::cout << "> ";
            }
        }
        ++round;
    }
    return 0;
}

std::vector<std::string> split(const std::string &str) {
    vector<string> tokens;
    istringstream iss(str);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));
    return tokens;
}

// trim from start
inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) { return !std::isspace(c); }));
    return s;
}

// trim from end
inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) { return !std::isspace(c); }).base(), s.end());
    return s;
}

// trim from both ends
inline std::string &trim(std::string &s) { return ltrim(rtrim(s)); }
