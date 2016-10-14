#include <iostream>
#include <vector>

using namespace std;

/**
 * push_back takes a container element and copies/moves it into the container.
 * emplace_back takes arbitrary arguments and constructs from those a new container element.
 * emplace_back performs explicit conversions
 * threads.emplace_back(do_work, 10, "foo");    // call do_work(10, "foo")
 */
void emplace_demo(){
    vector<int> v {};
    v.emplace_back(3);                          // { 3 }
    v.emplace_back(4);                          // { 3, 4 }
    v.emplace(v.begin(), 1);                    // { 1, 3, 4 }
    v.emplace(v.begin() + 1, 2);                // { 1, 2, 3, 4 }
    v.emplace(v.end(), 5);                      // { 1, 2, 3, 4, 5 }
}
int main(){
    vector<int> v(1, 0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    for(int ii=0; ii < v.size(); ii++){
        cout << v[ii] << endl;
    }

    for(vector<int>::const_iterator cii=v.begin(); cii!=v.end(); cii++){
        cout << *cii << endl;
    }

    for(vector<int>::reverse_iterator rii=v.rbegin(); rii!=v.rend(); ++rii){
        cout << *rii << endl;
    }

    cout << v.size() << endl;

    swap(v[0], v[2]);
    cout << v[2] << endl;

    if(!v.empty()){
        v.clear();
    }

    emplace_demo();
    return 0;
}