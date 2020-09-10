#include <getopt.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

char delimiter{','};
bool has_header{true};
bool sort_numerically{true};
string path{"/tmp/a.csv"};
string type{"sort"};
string head_line;
vector<int> field_idx;
vector<string> field_names;
vector<string> header_columns;
vector<string> contents;
string filter_condition;

void help() {
    cout << "Program options:" << endl;
    cout << "  -h                                    list help" << endl;
    cout << "  -p arg (=\"/tmp/a.csv\")              file path" << endl;
    cout << "  -t arg (=\"sort\")                    type (sort|extract|filter)" << endl;
    cout << "  -d arg (=\",\")                       delimiter" << endl;
    cout << "  -x                                    has header, when set, no header" << endl;
    cout << "  -y                                    sort mode, use text cmp instead of default numeric" << endl;
    cout << "  -n                                    column number, index from 0" << endl;
    cout << "  -f                                    field name" << endl;
    cout << "  -c                                    filter condition, like (>5, <3), only support numeric, for "
            "text filter, use grep"
         << endl;
    cout << "usage:\n";
    cout << "  csvutil -t sort -p a.csv -f c" << endl;
    cout << "  csvutil -t sort -p a.csv -n 2" << endl;
    cout << "  csvutil -t extract -p a.csv -f a,c" << endl;
    cout << "  csvutil -t extract -p a.csv -n 0,2" << endl;
    cout << "  csvutil -t filter -p a.csv -f a -c >3" << endl;
}

std::vector<std::string> split(const std::string& str, char delimiter_);
void print_selected(std::vector<std::string>& datum, std::vector<int> selected);
bool read_file();
bool parse_header();
void handle_sort();
void handle_extract();
void handle_filter();

int main(int argc, char** argv) {
    int opt;
    while ((opt = getopt(argc, argv, "hxyp:t:f:n:c:d:")) != -1) {
        switch (opt) {
            case 'x':
                has_header = false;
                break;
            case 'y':
                sort_numerically = false;
                break;
            case 'd':
                delimiter = *optarg;
                break;
            case 'p':
                path = std::string(optarg);
                break;
            case 't':
                type = std::string(optarg);
                break;
            case 'f':
                field_names = split(optarg, ',');
                break;
            case 'n':
                field_names = split(optarg, ',');
                for (auto& name : field_names) {
                    field_idx.push_back(std::stoi(name));
                }
                field_names.clear();
                break;
            case 'c':
                filter_condition = std::string(optarg);
                break;
            case 'h':
                help();
                return 0;
            default:
                abort();
        }
    }

    if (!read_file() || contents.empty()) {
        cerr << "file read failed or empty file " << path << endl;
        return 1;
    }
    if (!parse_header()) return 1;

    if (type == "sort") {
        handle_sort();
    } else if (type == "extract") {
        handle_extract();
    } else if (type == "filter") {
        handle_filter();
    } else {
        cerr << "unknown type " << type << endl;
    }
}

void handle_filter() {
    if (field_idx.empty() || filter_condition.empty()) {
        cerr << "filter field or condition not specified" << endl;
        return;
    }
    size_t filter_field_idx = field_idx.front();
    if (!header_columns.empty() && filter_field_idx >= header_columns.size()) {
        cerr << "filter field out of bound " << filter_field_idx << " >= " << header_columns.size() << endl;
        return;
    }
    bool cmp_great = true;
    if (filter_condition[0] == '>')
        cmp_great = true;
    else if (filter_condition[0] == '<')
        cmp_great = false;
    else {
        cerr << "unknown filter direction " << filter_condition[0] << endl;
        return;
    }
    double filter_val = std::stod(filter_condition.substr(1));

    cout << head_line << endl;
    for (const auto& line : contents) {
        vector<string> lets = split(line, delimiter);
        double val = std::stod(lets[filter_field_idx]);
        if ((cmp_great && val > filter_val) || (!cmp_great && val < filter_val)) cout << line << endl;
    }
}

void handle_extract() {
    if (field_idx.empty()) {
        cerr << "extract field not specified" << endl;
        return;
    }

    print_selected(header_columns, field_idx);
    for (const auto& line : contents) {
        vector<string> lets = split(line, delimiter);
        cout << "\n";
        print_selected(lets, field_idx);
    }
}

struct Entry {
    string line;
    double val;
    string val_str;
};

bool cmp_numeric(const Entry& l, const Entry& r) {
    if (std::isfinite(l.val) && std::isfinite(r.val))
        return l.val < r.val;
    else if (!std::isfinite(l.val) && !std::isfinite(r.val))
        return false;  // 永远让比较函数对相同元素返回false, otherwise violite Strict Weak Ordering
    else
        return !std::isfinite(l.val);
}

bool cmp_string(const Entry& l, const Entry& r) { return l.val_str < r.val_str; }

void handle_sort() {
    if (field_idx.empty()) {
        cerr << "sort field not specified" << endl;
        return;
    }
    size_t sort_field_idx = field_idx.front();
    if (!header_columns.empty() && sort_field_idx >= header_columns.size()) {
        cerr << "sort field out of bound " << sort_field_idx << " >= " << header_columns.size() << endl;
        return;
    }

    vector<Entry> datum;
    Entry entry;
    for (const auto& line : contents) {
        vector<string> lets = split(line, delimiter);
        entry.line = line;
        entry.val_str = lets[sort_field_idx];
        if (sort_numerically) {
            entry.val = std::stod(entry.val_str);
        }
        datum.push_back(entry);
    }

    if (sort_numerically)
        std::sort(datum.begin(), datum.end(), cmp_numeric);
    else
        std::sort(datum.begin(), datum.end(), cmp_string);

    cout << head_line << endl;
    for (const auto& entry_ : datum) cout << entry_.line << endl;
}

bool parse_header() {
    if (!has_header) return true;
    head_line = contents.front();
    contents.erase(contents.begin());  // remove head line
    header_columns = split(head_line, delimiter);
    if (!field_names.empty()) {
        for (const auto& name : field_names) {
            auto itr = std::find(header_columns.begin(), header_columns.end(), name);
            if (itr == header_columns.end()) {
                cerr << "column " << name << " not found!" << endl;
                return false;
            }
            field_idx.push_back(itr - header_columns.begin());
        }
    }
    return true;
}

bool read_file() {
    ifstream ifs(path, ifstream::in);

    if (ifs.is_open()) {
        string s;
        while (getline(ifs, s)) {
            if (!s.empty()) contents.push_back(s);
        }
        ifs.close();
        return true;
    } else {
        return false;
    }
}

void print_selected(std::vector<std::string>& datum, std::vector<int> selected) {
    int total_column = (int)selected.size();
    for (int i = 0; i < total_column - 1; ++i) {
        cout << datum[selected[i]] << ",";
    }
    cout << datum[selected.back()];
}

std::vector<std::string> split(const std::string& str, char delimiter_) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find(delimiter_);
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter_, start);
    }
    result.push_back(str.substr(start, end));
    return result;
}
