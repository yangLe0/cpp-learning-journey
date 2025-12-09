#include <iostream>
#include <vector>
using namespace std;
int main(int argc, char* argv[]){
    if(argc!= 3){
        cerr<<"Usage argc: "<< argc <<endl;
        cerr<<"Usage 1: "<<(argc>1?argv[1]:"null") <<endl;
        cerr<<"Usage 2: "<<(argc>2?argv[2]:"null") <<endl;
        cerr<<"Usage: "<<argv[0] <<" <num1> <num2>"<<endl;
        return 1;
    }
    //char* num_list_char = argv[1];
    //cout << "Usage 0: "<<argv[0] <<endl;
    // cout << "Usage 1: "<<argv[1] <<endl;
    std::string a = argv[1];
    std::string b = argv[2];
    int c = stoi(a) + stoi(b);
    std::string numStr = std::to_string(c);
    const char* res = numStr.c_str();
    
    //cout << "num_list[0]: " <<num_list[0];
    //cout << " num_list[1]: " << num_list[1] << endl;

    //char res = *a + *b;
    cout << ": " << numStr << endl;
    return 0;
}