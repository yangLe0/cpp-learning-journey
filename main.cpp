//
//  main.cpp
//  test
//
//  Created by 天塌不惊 on 2025/11/30.
//

#include <iostream>
#include <vector>
#include <numeric>
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
    // insert code here...
    cout << "please enter the length \n";
    int length = 0;
    cin >> length;
    
    vector<int> vec;
    vec.reserve(length);
    
    cout << "then enter "<<length<<" nums" << endl;
    for(int i=0;i<length;i++){
        int a;
        cin >> a;
        vec.push_back(a);
    }
    cout << "your enter: " ;
    printVector(vec);
    cout << "Sum is " << sumVector(vec) << endl;
    return 0;
}
