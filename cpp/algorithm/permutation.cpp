#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const vector<T>& v) {
    for (const auto& i : v) {
        os << i << " ";
    }
    return os;
}

/**
 * generate next choice,
 * max_choice_count[i] means in position i there are maximum max_choice_count[i] choices available
 * find first pos not equal maximum choice, add 1 and then set backward all 0
 */
bool next_choice(vector<int>& max_choice_count, vector<int>& choice) {
    int size = static_cast<int>(max_choice_count.size());
    for (int i = size - 1; i >= 0; --i) {
        if (choice[i] != max_choice_count[i] - 1) {
            ++choice[i];
            fill(choice.begin() + i + 1, choice.end(), 0);
            return true;
        }
    }
    return false;
}

// all n! permutation
void iterate_all_permutation(vector<int> v) {
    do {
        cout << v << endl;
    } while (next_permutation(v.begin(), v.end()));
}

// all n! permutation
void iterate_all_permutation_recursive(vector<int>& nums, int left, int size) {
    if (left == size - 1) {
        cout << nums << endl;
    } else {
        for (int i = left; i < size; i++) {
            swap(nums[left], nums[i]);
            iterate_all_permutation_recursive(nums, left + 1, size);
            swap(nums[left], nums[i]);
        }
    }
}

int main() {
    vector<int> v;
    v.resize(3);
    std::iota(v.begin(), v.end(), 3);
    iterate_all_permutation(v);

    cout << "all permutation recursive: " << endl;
    iterate_all_permutation_recursive(v, 0, v.size());

    cout << "variable choices: " << endl;
    vector<int> max_choice_count = {2, 1, 3};
    vector<int> choice(3, 0);
    do {
        cout << choice << endl;
    } while (next_choice(max_choice_count, choice));

    /**
     * 2^n choices
     */
    cout << "binary choices: " << endl;
    cout << boolalpha;
    int option_count = 3;
    int max_options = static_cast<int>(std::pow(2, option_count));
    vector<bool> chosen(option_count, false);
    for (int i = 0; i < max_options; ++i) {
        int tmp = i, index = 0;
        fill(chosen.begin(), chosen.end(), false);
        while (tmp > 0) {
            chosen[index++] = (tmp % 2 != 0);
            tmp /= 2;
        }
        cout << chosen << endl;
    }
    return 0;
}
