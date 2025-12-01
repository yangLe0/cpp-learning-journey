//
//  main.cpp
//  test
//
//  Created by 天塌不惊 on 2025/11/30.
//

#include <iostream>
#include <vector>
#include <numeric>
#include <limits> // 用于numeric_limits
#include <algorithm>
using namespace std;
void printVector(const vector<int>& vec){
    for (const int& elem : vec) {
        cout << elem << " ";
    }
    cout << endl;
}
int sumVector(const vector<int>& vec){
    return accumulate(vec.begin(), vec.end(), 0);;
}
int main(int argc, const char * argv[]) {
    cout << "please enter the length: ";
    int length = 0;
    cin >> length;
    
    vector<int> vec;
    vec.reserve(length);
    
    cout << "then enter "<<length<<" nums" << endl;
    for(int i=0;i<length;i++){
        int num;
        cin >> num;
        if(cin.fail()){
            cout << "please enter a num";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> num;
        }
        vec.push_back(num);
    }
    cout << "your enter: " ;
    printVector(vec);
    int sum = sumVector(vec);
    double average = static_cast<double>(sum) / length;
    cout << "Sum is " << sum << endl;
    if (!vec.empty()) {
        cout << "max is " << *max_element(vec.begin(), vec.end()) << endl;
        cout << "min is " << *min_element(vec.begin(), vec.end()) << endl;
        sort(vec.begin(), vec.end());
    }
    printVector(vec);
    cout << "average is " << average << endl;
    return 0;
}
