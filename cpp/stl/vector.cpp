#include <iostream>
#include <vector>
#include <string>

using namespace std;

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
}