//
//  matchtest.cpp
//  test
//
//  Created by 天塌不惊 on 2025/12/22.
//
/*
1、题目描述:

记账本上记录了若干条多国货币金额，需要转换成人民币分(fen)，汇总后输出每行记录一条金额，金额带有货币单位，格式为数字+单位，可能是单独元，或者单独分，或者元与分的组合要求将这些货币全部换算成人民币分(fen)后进行汇总，汇总结果仅保留整数，小数部分舍弃。元和分的换算关系都是1:100，如下:
1CNY=100fen(1元=100分)
1HKD=100cents (1港元=100港分)1JPY=100sen(1日元=100仙)
1EUR=100eurocents(1欧元=100欧分)
1GBP=100pence(1英镑=100便士)
汇率如下表

即100CNY=1825JPY=123HKD=14EUR=12GBP
输入描述:
第一行输入为N，N表示记录数。0<N<100之后N行，每行表示一条货币记录，且该行只会是一种货币。

输出描述:
将每行货币转换成人民币分(fen)后汇总求和，只保留整数部分输出格式只有整数数字，不带小数，不带单位
补充说明:
输出格式只有数字，不带单位
示例1
输入:
100CNY
输出:
10000
说明:
100CNY转换后是10000fen，所以输出结果为10000
示例2
输入:
3000fen
输出:
3000
 
 
2、题目

 设定一组四码的数字作为谜底，另一方猜每猜一个数，出数者就要根据这个数字给出提示，提示以XAYB形式呈现，直到猜中位置。其中X表示位置正确的数的个数(数字正确且位置正确)，而Y表示数字正确而位置不对的数的个数例如，当谜底为8123，而猜谜者猜1052时，出题者必须提示0A2B。例如，当谜底为5637，而猜谜者猜4931时，出题者必须提示1A0B。当前已知N组猜谜者猜的数字与提示，如果答案确定，请输出答案，不确定则输出NA

 输入描述
 第一行输入一个正整数，0<N<100.
 接下来N行，每一行包含一猜测的数字与提示结果
 输出描述
 输出最后的答案，答案不确定则输出NA.
 示例1:
 输入
 6
 4815 1A1B
 5716 0A1B
 7842 0A1B
 4901 0A0B
 8585 3A0B
 8555 2A1B
 输出
 3585
 
 3、题目描述
 给定一些短词字符串作为分割词，去分割一段长字符串。从前往后遍历分割词，查找并分割长字符串为对应的token。分词规则如下:
 1.优先匹配最长分割词:若多个分割词可匹配同一位置，选择长度最长的:长度相同时，按字典序较大的优先

 2.未匹配部分保留原样:无法匹配分割词的部分直接作为独立token输出。

 3.输出格式:每个token用括号包裹，按原字符串顺序输出。
 输入描述:
 短词字符串列表，每行一个，空行后输入待分割的长字符串。
 输出描述:
 括号包裹的分词结果，如(token1)(token2)
 示例1:
 输入:
 zhong guo
 zhong
 guo
 wo
 mei guo
 wo ai zhong guo mei guo ye xing
 输出:
 (wo)(ai)(zhong guo)(mei guo)(ye)(xing)
*/
#include <stdio.h>
#include <iostream>
#include <map>
#include <sstream>
using namespace std;
int anahuobi(const string& huobi){
    int res=0;
    //有5种货币，还有分，10种
    unordered_map<string,int> huilv={
        {"CNY",100},{"JPY",1825},{"HKD",123},{"EUR",14},{"GBP",12},
        {"fen",10000},{"sen",182500},{"cents",12300},{"eurocents",1400},{"pence",1200}
    };
    //分开数字和字符，可能有元有分
    //unordered_map<string, int> money;
    string yun,fen,num;
    vector<string> nums;//元、分
    for (char c : huobi) {
        if (c>='0'&&c<='9') {
            num+=c;
        }else if (c>='A'&&c<='Z'){
            if (!num.empty()) {
                nums.push_back(num);
                num.clear();
            }
            yun+=c;
        }else if(c>='a'&&c<='z'){
            if (!num.empty()) {
                nums.push_back(num);
                num.clear();
            }
            fen+=c;
        }
        
    }
    for(string ele:nums){cout<<"ele: "<<ele<<endl;}
    if (nums.empty()) {
        return 0;
    }
    cout << "yun: " << yun<<" fen: "<<fen<<endl;
    //加元分
    if(huilv.count(yun) && huilv.count(fen)){
        res=stoi(nums[0])*10000/huilv[yun]+stoi(nums[1])*10000/huilv[fen];
        cout <<"res1/2: "<<res<<endl;
    }
    else if (huilv.count(yun)==0&&huilv.count(fen)){
        res=stoi(nums[0])*10000/huilv[fen];
        //cout <<"res1: stoi(nums[0])"<<stoi(nums[0])<<endl;
        //cout <<"huilv[fen]: "<<huilv[fen]<<endl;
        //cout <<"res1:"<<res<<endl;
    }else if (huilv.count(yun)&&huilv.count(fen)==0){
        res=stoi(nums[0])*10000/huilv[yun];
        cout <<"res2: "<<res<<endl;
    }
    
    return res;
}
void question1(){
    int N,sum=0;
    cin >> N;
    cin.ignore();
    
    for(int i=0;i<N;i++){
        string huobi;
        //分析是什么货币
        cin >> huobi;
        sum+=anahuobi(huobi);
    }
    cout << sum;
}
struct guess{
    string guessNum;
    int A;
    int B;
};
void calculateAB(const string& temp,const string& ele,int &A,int& B){
    A=0;
    B=0;
    vector<bool> used_temp(4,false);
    vector<bool> used_ele(4,false);
    for(int i=0;i<4;i++){
        if (temp[i]==ele[i]) {
            A++;
            used_temp[i]=true;
            used_ele[i]=true;
        }
    }
    for(int i=0;i<4;i++){
        if(used_temp[i])continue;
        for(int j=0;j<4;j++){
            if(used_ele[j])continue;
            if(temp[i]==ele[j]){
                B++;
                used_temp[i]=true;
                used_ele[j]=true;
                break;
            }
        }
    }
}
bool isMatch(const string & temp, const vector<guess>& guessHints){
    //检查某个数字串是否满足输入提示
    for(const guess& ele:guessHints){
        int A,B;
        calculateAB(temp,ele.guessNum,A,B);
        if(ele.A!=A||ele.B!=B){
            return false;
        }
    }
    return true;
}
void question2(){
    int N;
    cin >> N;
    vector<guess> guessHints;
    
    for(int i=0;i<N;i++){
        string guess, response;
        cin>>guess>>response;
        int A = response[0]-'0';
        int B = response[2]-'0';
        guessHints.push_back({guess,A,B});
    }
    vector<string> res;
    for(int i=0;i<10000;i++){
        string temp = to_string(i);
        while(temp.length()<4){
            temp='0'+temp;
        }
        if(isMatch(temp,guessHints)){
            res.push_back(temp);
        }
    }
    if (res.size()==1) {
        cout << res[0]<<endl;
    }else{
        cout<<"NA"<<endl;
    }
}
bool comparewords(const string&a,const string& b){
    if (a.length()!=b.length()) {
        return a.length()>b.length();
    }
    return a>b;
}
vector<string> splitBySpace(const string& s){
    vector<string> res;
    stringstream ss(s);
    string word;
    while(ss>>word){
        res.push_back(word);
    }
    return res;
}
string joinWords(const vector<string>& wordlist, int pos, int k){
    string res = wordlist[pos];
    for(int i=1;i<k;i++){
        res += " " + wordlist[i+pos];
    }
    return res;
}
/*
 zhong guo
 zhong
 guo
 wo
 mei guo

 wo ai zhong guo mei guo ye xing
 */
void question3(){
    vector<string> duanciVec;
    string line;
    while(getline(cin,line)){
        if(line.empty()){
            break;
        }
        duanciVec.push_back(line);
    }
    string changci;
    getline(cin,changci);
    
    sort(duanciVec.begin(),duanciVec.end(),comparewords);

    //分割
    vector<string> changciFengeVec = splitBySpace(changci);
    
    vector<string> token;
    int pos=0;
    int n = changciFengeVec.size();
    
    while(pos<n){
        bool match = false;
        for (const string& duanci:duanciVec) {//短词
            vector<string> duanciFengeVec = splitBySpace(duanci);
            int duancicount = duanciFengeVec.size();
            if(pos+duancicount>n)continue;
            string temp = joinWords(changciFengeVec,pos,duancicount);
            cout<<"jointemp: "<<temp<<" "<<"  duanci: "<<duanci<<endl;
            //string subStr = targetStr.substr(pos,wordlen);
            if (temp==duanci) {
                token.push_back(duanci);
                pos+=duancicount;
                match = true;
                break;
            }
        }
        if(!match){
            //token.push_back(targetStr.substr(pos,1));
            token.push_back(changciFengeVec[pos]);
            pos++;
        }
    }
    string res;
    for(const string& to:token){
        res += "("+to+")";
    }
    cout <<res;
}
int main(){
    question1();
    return 0;
}
