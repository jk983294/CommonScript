#include <iostream>
#include <vector>
#include <algorithm>
#include <ios>
using namespace std;

template<typename T>
inline std::ostream& operator << (std::ostream& os, const vector<T>& v)
{
    const int size = v.size();
    if(size > 0){
        for (int i = 0; i < size-1; i++)
            os << v[i] << " ";
        os << v[size-1];
    }
    return(os);
}

/**
 * generate next choice,
 * max_choice_count[i] means in position i there are maximum max_choice_count[i] choices available
 * find first pos not equal maximum choice, add 1 and then set backward all 0
 */
bool next_choice(vector<int> &max_choice_count, vector<int> &choice){
    for (int i = max_choice_count.size() - 1; i >= 0; --i){
        if(choice[i] != max_choice_count[i] - 1){
            ++choice[i];
            fill(choice.begin() + i + 1, choice.end(), 0);
            return true;
        }
    }
    return false;
}

// generate sequence from 0 -> N - 1
void generate_sequence(vector<int> &index, int count){
    index.resize(count);
    for (int i = 0; i < count; ++i)	index[i] = i;
}
// all n! permutation
void iterate_all_permutation(vector<int> v){
    do {
        cout << v << endl;
    } while (next_permutation(v.begin(), v.end()));
}


int main() {
    vector<int> v;
    generate_sequence(v, 3);
    iterate_all_permutation(v);

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
    cout<<boolalpha;
    int option_count = 3;
    int max_options = pow(2, option_count);
    vector<bool> chosen(option_count, false);
    for (int i = 0; i < max_options; ++i){
        int tmp = i, index = 0;
        fill(chosen.begin(), chosen.end(), false);
        while(tmp > 0){
            chosen[index++] = (tmp % 2 != 0);
            tmp /= 2;
        }
        cout << chosen << endl;
    }

    return 0;
}