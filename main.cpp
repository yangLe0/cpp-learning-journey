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
#include <fstream>
#include <map>
#include <string>
//#include <sstream>
using namespace std;

const string FILE_NAME = "recordNum.txt";

void printVector(const vector<int>& vec){
    for (const int& elem : vec) {
        cout << elem << " ";
    }
    cout << endl;
}
int sumVector(const vector<int>& vec){
    return accumulate(vec.begin(), vec.end(), 0);;
}
//用户输入数据
vector<int> readUserVector(int length){
    vector<int> vec;
    vec.reserve(length);
    cout << "enter " << length << " numbers:" << endl;
    
    for(int i=0;i<length;i++){
        cout << "enter " << i+1 << " nums" << endl;
        int num;
        while(!(cin >> num)){
            cout << "Invalid input! Please enter a number " << i+1<<":";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        vec.push_back(num);
    }
    return vec;
}
int maxVector(const vector<int>& vec){
    return *max_element(vec.begin(), vec.end());
}
int minVector(const vector<int>& vec){
    return *min_element(vec.begin(), vec.end());
}
//保存到文件
void SaveFile(const vector<int>& vec){
    ofstream out(FILE_NAME);
    if (!out.is_open()) {
        cerr << "Error: Cannot create file " << FILE_NAME << endl;
        return;
    }
    /*
    for (auto element : vec) {
        out << element << " ";
    }*/
    //filesystem::remove(file_path);
    copy(vec.begin(), vec.end(), ostream_iterator<int>(out, " "));
}
//读取文件
vector<int> LoadFile(){
    vector<int> vec;
    ifstream in(FILE_NAME);
    in.exceptions(ifstream::failbit | ifstream::badbit);
    int num;
    while (in >> num) {
        vec.push_back(num);
    }
    /*string line;
    if (getline(in, line)) {
        stringstream ss(line);
        int num;
        while(ss >> num){
            vec.push_back(num);
        }
    }*/
    return vec;
}
double AverageVector(const vector<int>& vec){
    /*if(length == 0){
        cout << "Length can't be zero!" << endl;
        return 1;
    }*/
    if(vec.empty()) throw invalid_argument("Vector is empty");
    return static_cast<double>(sumVector(vec)) / vec.size();
}
int main(int argc, const char * argv[]) {
    try {
        cout << "please enter length: ";
        int length = 0;
    
        if (!(cin >> length) || length == 0) {
            throw invalid_argument("Length must be positive");
        }
    vector<int> vec = readUserVector(length);

    cout << "your enter: " ;
    printVector(vec);
    
    SaveFile(vec);
    int sum = sumVector(vec);
    //double average = static_cast<double>(sum) / length;
    cout << "Sum is " << sum << endl;
    if (!vec.empty()) {
        cout << "max is " << maxVector(vec) << endl;
        cout << "min is " << minVector(vec) << endl;
        sort(vec.begin(), vec.end());
    }
    printVector(vec);
    cout << "average is " << AverageVector(vec) << endl;
    
    auto LoadVec = LoadFile();
    printVector(LoadVec);
    
    cout << "enter the num you want to find: ";
    int findNum = 0;
    cin >> findNum;
    
    auto res = find(LoadVec.begin(), LoadVec.end(), findNum);
    if(res != LoadVec.end()){
        cout << "Found at index:" << (res-LoadVec.begin()) << endl;
    }else{
        cout << "not find the num" << endl;
    }
    
    map<int,int> NumCount;
    for(auto element : LoadVec){
        NumCount[element]++;
        /*auto pos = NumCount.find(element);
        if (pos != NumCount.end()) {
            (*pos).second++;
        }else{
            NumCount[element]=1;
        }*/
    }
    for (auto mapEle : NumCount) {
        cout << mapEle.first << " " << mapEle.second << endl;
    }
    } catch(const ios_base::failure& e){
        cerr << "File error: " << e.what() << endl;
    }catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}
