#include <algorithm>
#include <functional>
#include <iostream>
#include <tuple>

class TableGenerator {
    using TableT = std::vector<std::tuple<std::string, std::size_t> >;

private:
    auto const& add_word() {
        table_.emplace_back(word_, hFunc(word_));
        return table_.back();
    }

public:
    TableGenerator(std::string alphabet) : word_{alphabet} { std::sort(word_.begin(), word_.end()); }

    bool operator()(std::string& word, std::size_t& hash) {
        if (!std::next_permutation(word_.begin(), word_.end())) return false;

        std::tie(word, hash) = add_word();
        return true;
    }

private:
    TableT table_;
    std::string word_;
    std::hash<std::string> hFunc;
};

int main() {
    TableGenerator tableGenerator("jqinv");

    std::string word;
    std::size_t hash = 0;
    while (tableGenerator(word, hash)) {
        std::cout << word << " " << std::hex << hash << "\n";
    }
    return 0;
}
