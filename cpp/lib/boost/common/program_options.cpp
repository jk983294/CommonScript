#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

// give option in vs: Configuration Properties -> Debugging -> Command Arguments
// --filename my.txt -V 21 --files a.txt b.txt c.txt
int main(int argc, char *argv[])
{
    int value;                                          // bind argument to variable
    po::options_description desc("Program options");
    desc.add_options()
        ("help", "print info")
        ("filename", po::value<string>()->default_value("default.txt"), "file to process")
        ("value,V", po::value<int>(&value)->default_value(42), "input value")
        ("files", po::value<vector<string>>()->multitoken(), "input files");

    po::variables_map vm;
    auto parsed = po::parse_command_line(argc, argv, desc);
    po::store(parsed, vm);
    po::notify(vm);

    if (vm.count("help"))                               // check if help argument provided
        cout << desc << endl;

    string filename = vm["filename"].as<string>();      // retrieve arguments
    cout << "process file: " << filename << endl;
    cout << "value is: " << value << endl;

    if (vm.count("files")){
        int i = 0;
        auto files = vm["files"].as<vector<string>>();
        for (auto s : files)
            cout << (++i) << ": " << s << endl;
    }

    /**
     * position arguments demo, like main.exe a.txt b.txt c.txt
     */
    po::positional_options_description pos;
    pos.add("files", -1);

    po::variables_map vm1;
    po::command_line_parser parser(argc, argv);
    auto parsed_options = parser.options(desc).positional(pos).run();
    po::store(parsed_options, vm1);
    po::notify(vm1);

    if (vm1.count("files")){
        int i = 0;
        auto files = vm1["files"].as<vector<string>>();
        for (auto s : files)
            cout << (++i) << ": " << s << endl;
    }

    getchar();
    return 0;
}