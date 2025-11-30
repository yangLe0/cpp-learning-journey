//
//  main.cpp
//  test
//
//  Created by 天塌不惊 on 2025/11/30.
//

#include <iostream>
#include <vector>
using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Hello, World!\n";
    vector<int> vec = {1,2,3,4};
    vec.push_back(5);
    int sum = 0;
    for (int i=0; i<vec.size(); i++) {
        cout << vec[i] << " ";
        sum += vec[i];
    }
    cout << sum << endl;
    return 0;
}
