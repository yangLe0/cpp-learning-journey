//
//  ncquestions.cpp
//  test
// NC52 有效括号序列给出一个仅包含字符仅由括号字符 ‘[’‘[’、‘]’‘]’、‘(’‘(’、‘)’‘)’、‘{’‘{’、‘}’‘}’ 的括号序列字符串 s*s*（0≦∣s∣≦1040≦∣*s*∣≦104），你需要判断给出的括号序列字符串 s*s* 是否是有效的括号序列。
//有效括号序列的定义如下：∙ ∙空序列是有效括号序列；∙ ∙如果 A*A* 是有效括号序列，则 (A)(A)、[A][A] 和 AA 都是有效括号序列；∙ ∙如果 A*A* 和 B*B* 都是有效括号序列，则它们的拼接 AB*AB* 也是有效括号序列。
//如果括号序列字符串 s*s* 是有效的括号序列，返回一个布尔值 truetrue；否则返回一个布尔值 falsefalse。
//1、给定一个非空字符串S，其被N个‘-’分隔成N+1的子串，给定正整数K，要求除第一个子串外，其余的子串每K个字符组成新的子串，并用‘-’分隔。对于新组成的每一个子串，如果它含有的小写字母比大写字母多，则将这个子串的所有大写字母转换为小写字母；反之，如果它含有的大写字母比小写字母多，则将这个子串的所有小写字母转换为大写字母；大小写字母的数量相等时，不做转换。
//输入描述:输入为两行，第一行为参数K，第二行为字符串S。
//输出描述:输出转换后的字符串。
//示例1
//输入 3 12abc-abCABc-4aB@
//输出 12abc-abc-ABC-4aB-@
//  Created by 天塌不惊 on 2025/12/19.
//

#include <stack>
#include <iostream>
#include <string>
#include <map>
using namespace std;
bool isValid(string s){
    unordered_map<char, char> blacketmap = {
        {')','('},{']','['},{'}','{'}
    };
    stack<char> st;
    for(char c : s){
        if (blacketmap.count(c)) {
            if (st.empty() || st.top()!=blacketmap[c]) {
                return false;
            }
            st.pop();
        }else{
            st.push(c);
        }
    }
    return st.empty();
}
vector<string> str_split(const string& str, char mark){
    vector<string> result;
    string temp;
    for(const char&c : str){
        if (c == mark) {
            //cout<<"temp: "<<temp<<endl;
            result.push_back(temp);
            temp="";
            continue;
        }
        temp+=c;
    }
    result.push_back(temp);
    return result;
}
void UpOrLow(string& temp){
    int uplen=0,lowlen=0;
    string res;
    for(const char&c:temp){
        if (isupper(c)) {
            uplen++;
        }else if(islower(c)){
            lowlen++;
        }
    }
    //cout <<"uplen:"<<uplen<<endl;
    //cout <<"lowlen:"<<lowlen<<endl;
    if (uplen>lowlen) {
        for(char&c:temp){
            c=toupper(c);
        }
    }else if (lowlen>uplen){
        for(char&c:temp){
            c=tolower(c);
        }
    }
    //cout<<"temp:"<<temp<<endl;
}
void questionOne(){
    int K;
    string strOrigin;
    cin >> K;
    cin.ignore();
    getline(cin, strOrigin);
    //字符根据-分割
    vector<string> subStrOrigin = str_split(strOrigin, '-');
    string firstStr = subStrOrigin[0];//拿到第一个子串
    string withoutFirstStr;
    
    for(int i=1;i<subStrOrigin.size();i++)
    {
        withoutFirstStr+=subStrOrigin[i];//除了第一个子串外的所有字符
    }
    //cout << "withoutFirstStr: "<<withoutFirstStr<<endl;
    //按k分割
    vector<string> kstr;
    for (int i=0; i<withoutFirstStr.size(); i+=K) {
        string temp = withoutFirstStr.substr(i,K);
        UpOrLow(temp);
        kstr.push_back(temp);
    }
    //分割后输出
    cout<<firstStr;
    for(const string&ele:kstr){
        cout<<"-"<<ele;
    }
}
int main(){
    //string s1 = "()[]{}";
    //cout << "测试用例1 \"" << s1 << "\": " << (isValid(s1) ? "有效" : "无效") << endl;
    //3 12abc-abCABc-4aB@
    questionOne();
    return 0;
}
