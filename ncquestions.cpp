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
#include <sstream> // 处理复杂分割必备
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
void stringchar(){
    // 1. 空字符串
    string s1;
    s1 = "abc";
    s1.assign("def");       // 清空s1并将其内容替换为括号里的，等价于 s1 = "def"
    //cout <<s1<<endl; //def
    s1.assign("ghijk", 3);  // 取前3个字符，s1 = "ghi"
    //cout <<s1<<endl; //ghi
    // 拼接（+= 是最常用方式）
    s1 += "123";            // s1 = "ghi123"
    s1.append("456");       // 等价于 +=，s1 = "ghi123456"
    s1.push_back('7');      // 追加单个字符，s1 = "ghi1234567"
    
    // 2. 直接赋值字符串常量
    string s2 = "Hello C++";
    string s3("Hello World");
    
    // 3. 重复字符初始化（n个字符c）
    string s4(5, 'a');  // s4 = "aaaaa"
    
    // 4. 从另一个string截取（起始位置pos，长度len）
    string s5(s2, 0, 5);  // s5 = "Hello"（从s2的0位置取5个字符）
    
    // 5. 从字符数组初始化
    char arr[] = "test";
    string s6(arr);
    
    // 字符串拼接（两个string/字符串常量）
    string s7 = s2 + " " + s3;  // s7 = "Hello C++ Hello World"
    
    // 方式1：[] 访问（无越界检查，速度快，访问越界会导致未定义行为（程序崩溃））
    char c1 = s7[0];  // c1 = 'H'
    s7[1] = 'B';      // s7 = "HBllo C++ Hello World"
    
    // 方式2：at() 访问（有越界检查，抛出异常，更安全，新手优先用 at()）
    char c2 = s7.at(2);  // c2 = 'l'
    //cout << s7.at(100);  // 越界，抛出 std::out_of_range 异常
    
    // 方式3：迭代器（遍历用）
    for (string::iterator it = s7.begin(); it != s7.end(); ++it) {
        cout << *it << " ";  // 输出：H B l l o   C + +   H e l l o   W o r l d
    }
    cout<<endl;
    // 核心：获取有效字符数（常用）
    int len1 = s7.size();    // len1 = 21
    int len2 = s7.length();  // 等价于 size()，len2 = 21
    
    // 容量（已分配的内存能容纳的字符数，≥ size()）
    int cap = s7.capacity();  // 随编译器不同，比如 22
    
    // 判空
    bool is_empty = s7.empty();  // false 0
    s7.clear();                  // 清空字符串，s 变为空
    is_empty = s7.empty();       // true 1
    
    // 预留容量（减少内存重新分配，提升性能）大量字符串拼接时，优先用 reserve() 预留容量，避免频繁内存重分配
    s7.reserve(100);  // 预分配能存100个字符的内存
    
    string s = "hello world, hello c++";
    // 1. 查找字符串
    size_t pos1 = s.find("hello");    // pos1 = 0（首次出现位置）
    size_t pos2 = s.find("hello", 1); // 从位置1开始找，pos2 = 13
    
    // 2. 查找字符
    size_t pos3 = s.find('w');        // pos3 = 6
    
    // 3. 反向查找（rfind）：从末尾找首次出现位置
    size_t pos4 = s.rfind("hello");   // pos4 = 13
    
    // 4. 判读是否找到
    if (s.find("java") == string::npos) {//找不到返回 string::npos（一个常量,无符号整数（size_t 类型），值为 -1，判断时不要用 == -1，直接用 == string::npos）
        cout << "未找到 java" << endl;
    }
    
    // 替换 replace(起始位置, 替换长度, 新字符串)
    s.replace(6, 5, "C++");  // 从位置6开始，替换5个字符为"C++"
    cout << s << endl;       // 输出：hello C++, hello c++
    
    // 插入：insert(起始位置, 插入内容)
    s.insert(2, "123");  // 位置2插入"123"，s = "he123llo C++, hello c++"
    
    // 删除：erase(起始位置, 删除长度)
    s.erase(2, 3);       // 从位置2删除3个字符，s 回到 "hello C++, hello c++"
    
    // 截取字符串 substr(起始位置, 截取长度)，长度省略则取到末尾
    string sub1 = s.substr(6);    // 从位置6取到末尾，sub1 = "C++, hello c++"
    string sub2 = s.substr(0, 5); // 从位置0取5个字符，sub2 = "hello"
    
    // 字符串与数值互转（C++11+ 推荐）
    // 1）数值 → 字符串
    // 方法1：to_string（支持int/float/double等）
    int num = 123;
    double d = 3.14;
    string s8 = to_string(num);  // s1 = "123"
    string s9 = to_string(d);    // s2 = "3.140000"
    
    // 2）字符串 → 数值
    string s_num = "123";
    string s_d = "3.14";
    
    // stoi/stol/stoll：转整数（int/long/long long）
    num = stoi(s_num);         // num = 123
    
    // stof/stod/stold：转浮点数（float/double/long double）
    d = stod(s_d);        // d = 3.14
    
    // 注意：字符串格式错误会抛异常，比如 stoi("abc") → 抛出 std::invalid_argument
    
    // 字符串比较 支持直接用 ==/!=/>/< 等运算符（按 ASCII 码逐字符比较）
    s1 = "abc";
    s2 = "abd";
    s3 = "abc";
    
    cout << (s1 == s3) << endl;  // 1（true）
    cout << (s1 < s2) << endl;   // 1（true，'c' < 'd'）
    cout << (s1 > "aaa") << endl;// 1（true）
    
    // 也可用 compare 方法（返回0:相等; <0:s1<s2; >0:s1>s2）
    int res = s1.compare(s2);   // res = -1
    
    // 与 C 语言字符数组互转
    s = "hello";
    // string → char*（c_str() 返回 const char*，不可修改）
    const char* arr1 = s.c_str();
    // string → char*（data() C++17后可返回 char*，之前是 const char*）
    const char* arr2 = s.data();
    
    // char* → string（直接赋值即可）
    char arr3[] = "world";
    s1 = arr3;
}
void stringchar2(){
    // 1. 普通输入（遇空格/回车终止）
    string s1;
    cin >> s1; // 输入：hello world → s1 = "hello"
    
    // 2. 整行输入（含空格）
    cin.ignore(); // 清空缓冲区（避免读取上一次的回车）
    string s2;
    getline(cin, s2); // 输入：hello world → s2 = "hello world"
    
    // 3. 输出（直接输出/拼接输出）
    cout << s2 << endl; // 输出：hello world
    cout << s2.substr(0, 5) + " C++" << endl; // 输出：hello C++
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
vector<string> split(const string&s ,char delimiter){
    vector<string> res;
    string temp;
    for(char c:s){// 范围for遍历（简洁高效）
        if(c!=delimiter){
            temp+=c;
        }else{
            if(!temp.empty()){// 避免空串（如连续分隔符）
                res.push_back(temp);
                temp.clear();
            }
        }
    }
    if(!temp.empty()){// 处理最后一个子串
        res.push_back(temp);
    }
    return res;
}
void test(){
    string s = "123,456,789";
    vector<string> parts = split(s, ',');
    for (string part : parts) {
        cout << part << endl; // 输出：123 456 789
    }
}
// 统计字符频次（ASCII字符，用数组更高效）
void count_chars(const string& s){
    int count[128] = {0};// ASCII码范围0-127，初始化为0
    for(char c:s){
        count[(int)c]++;// 字符转ASCII码作为下标
    }
    for(int i=0;i<128;i++){
        if(count[i]>0){
            cout<<(char)i<<": "<<count[i]<<endl;
        }
    }
}
// 1. 反转字符串（两种方法）
string reverse_str(string s){
    // 方法1：用algorithm的reverse
    //reverse(s.begin(),s.end());
    // 方法2：手动反转（理解原理）
    int left=0,right=s.size()-1;
    while(left<right){
        swap(s[left],s[right]);
        left++;
        right--;
    }
    return s;
}
// 2. 判断回文字符串（忽略大小写/空格)
bool is_palindrome(string s){
    // 预处理：转小写 + 去掉非字母数字（可选)
    string temp;
    for(char c:s){
        if(isalnum(c)){// 判断是否为字母/数字
            temp += tolower(c);// 转小写
        }
    }
    // 双指针判断
    int left=0,right=temp.size()-1;
    while(left<right){
        if(temp[left]!=temp[right]){
            return false;
        }
        left++;
        right--;
    }
    return true;
}
// 替换所有指定子串
string replace_all(string s,const string& old_str,const string& new_str){
    size_t pos = 0;
    while((pos=s.find(old_str,pos))!=string::npos){
        s.replace(pos,old_str.size(),new_str);
        pos+=new_str.size();// 跳过新替换的内容，避免重复替换
    }
    return s;
}
void test2(){
    //string s = "abacb";
    //count_chars(s);// 测试：输入 "abacb" → a:2, b:2, c:1
    //cout << reverse_str("hello") << endl; // 输出：olleh
    //cout << is_palindrome("A man, a plan, a canal: Panama") << endl; // 输出：1（true）
    // 1. 数值转字符串
    int a = 123;
    double b = 3.1415;
    string sa = to_string(a);
    string sb = to_string(b);
    // 2. 字符串转数值（处理异常）
    string s1 = "456";
    string s2 = "78.9";
    int num1 = stoi(s1);
    double num2 = stod(s2);
    // 3. 实战：字符串分割后求和
    string s = "10,20,30,40";
    vector<string> parts = split(s,',');
    int sum=0;
    for(string part:parts){
        sum+=stoi(part);
    }
    cout<<sum<<endl;
    s = "abc123abc456abc";
    string res = replace_all(s, "abc", "xyz");
    cout << res << endl; // 输出：xyz123xyz456xyz
}
void test3(){
    // 1. 处理多行输入（直到EOF)
    string line;
    vector<string> lines;
    while(getline(cin,line)){// 按行读取，直到Ctrl+D（Linux）/Ctrl+Z（Windows）
        if(line.empty())// 空行终止
            break;
        lines.push_back(line);
    }
    // 2. 处理超长字符串（避免内存问题）
    string long_str;
    long_str.reserve(100000); // 预分配10万字符空间，避免频繁扩容
    //cin >> long_str;
    // 3. 混合分隔符分割（如空格+逗号，用stringstream）
    string mix_str = "123,456 789|000";
    stringstream ss(mix_str);
    string token;
    while(getline(ss,token,',')){
        stringstream ss2(token);
        string sub_token;
        while (getline(ss2,sub_token,' ')) {
            cout<<sub_token<<" ";
        }
    }
}
// 通用Trim函数（去除首尾指定字符，默认空格/制表符）
string trim(const string& s, const string& chars = " \t\n\r") {
    // 1. 找到第一个不在chars里的字符的位置（跳过开头的指定字符）
    size_t start = s.find_first_not_of(chars);
    // 如果整个字符串都是要去除的字符，返回空字符串
    if (start == string::npos) {
        return "";
    }
    // 2. 找到最后一个不在chars里的字符的位置（跳过结尾的指定字符）
    size_t end = s.find_last_not_of(chars);
    
    // 调试输出（可以删掉，仅用于看过程）
    cout << "原字符串s: \"" << s << "\"" << endl;
    cout << "第一个有效字符位置start: " << start << endl;
    cout << "最后一个有效字符位置end: " << end << endl;
    
    // 3. 截取从start开始，长度为 (end - start + 1) 的子串
    // 错误点：原代码是 end - start - 1，会少截最后一个字符
    return s.substr(start, end - start + 1);
}
void test4(){
    string s = "  abc 123,,  ";// 测试：输入 "  abc 123,,  " → 输出 "abc 123,,"
    cout << trim(s) << endl;
    // 去除首尾逗号：trim(s, ", ") → 输出 "abc 123"
    cout << trim(s, ", ") << endl;
}
// 1. 字符串压缩（统计连续字符频次）
string compress_str(const string& s){
    if(s.empty())return "";
    string res;
    res.reserve(s.size());
    char cur=s[0];
    int count=1;
    for(int i=1;i<s.size();i++){
        if(s[i]==cur){
            count++;
        }else{
            res+=cur+to_string(count);
            cur=s[i];
            count=1;
        }
    }
    cout<<res<<endl;
    res+=cur+to_string(count);
    return res;
}
// 2. 字符串解压缩（数字可能多位，如"a10b2"→"aaaaaaaaaabb"）
string decompress_str(const string & s){
    string res;
    string num_str;
    for(char c:s){
        if (isalpha(c)) {// 字母
            if (!num_str.empty()) {// 有数字待处理
                int num = stoi(num_str);
                res.append(num-1,res.back());// 重复最后一个字符
                num_str.clear();
            }
            res+=c;
        }else if(isdigit(c)){// 数字（支持多位）
            num_str+=c;
        }
    }
    if(!num_str.empty())
        res.append(stoi(num_str)-1,res.back());// 减1是因为字母已加过1次
    return  res;
}
void test5(){
    string s1 = "aaabbc";
    cout << compress_str(s1) << endl; // 输出：a3b2c1
    string s2 = "a10b2";
    cout << decompress_str(s2) << endl; // 输出：aaaaaaaaaabb
    string s3 = "a3b2c1";
    cout << decompress_str(s3) << endl; // 输出：aaabbc
    string s4 = "aaaa";
    cout << compress_str(s4) << endl; // 输出：a4
    string s5 = "ab";
    cout << compress_str(s5) << endl; // 输出：a1b1
}
int length_of_longest_substring(const string& str){
    if (str.empty()) {
        return 0;
    }
    char count[127]={0};
    int left=0,maxlen=0;
    for (int right=0;right<str.size();right++) {
        char c = str[right];
        cout << "c:"<<c<<endl;
        if(left<count[(int)c]){
            left=count[(int)c];
        }
        cout<<"count[c]:"<<count[(int)c]<<endl;
        cout<<"left:"<<left<<endl;
        count[(int)c]=right+1;
        cout<<"count[c]:"<<count[(int)c]<<endl;
        cout<<"right+1:"<<right+1<<endl;
        maxlen=max(maxlen,right-left+1);
    }
    return maxlen;
}
void test6(){
    cout << length_of_longest_substring("abcabcbb") << endl; // 3
    cout << length_of_longest_substring("bbbbb") << endl;    // 1
    cout << length_of_longest_substring("pwwkew") << endl;   // 3
}
bool check_password(const string& password){
    if (password.size()<8) {
        return false;
    }
    bool has_lower=false,has_upper=false,has_digit=false,has_special=false;
    string speicalStr = "!@#$%^&*";
    for(int i=0;i<password.size();i++){
        if (i>0&&password[i]==password[i-1]) {
            return false;
        }
        if (isupper(password[i])) {
            has_upper=true;
        }else if(islower(password[i])){
            has_lower=true;
        }else if(isdigit(password[i])){
            has_digit=true;
        }else if (speicalStr.find(password[i])!=string::npos){
            has_special=true;
        }else{
            return false;
        }
    }
    return has_lower&&has_digit&&has_upper&&has_special;
}
void test7(){
    cout << check_password("Abc123!@") << endl;    // 1（合法）
    cout << check_password("abc123!@") << endl;    // 0（无大写）
    cout << check_password("Abc123!!") << endl;    // 0（连续重复）
}
// 生成next数组（部分匹配表）
vector<int> getNext(const string& pattern) {
    int m = pattern.size();
    vector<int> next(m, 0);
    int j = 0; // 前缀指针

    for (int i = 1; i < m; ++i) {
        // 不匹配时，回退j到next[j-1]
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }
        // 匹配时，j前进，更新next[i]
        if (pattern[i] == pattern[j]) {
            j++;
            next[i] = j;
        }
    }
    return next;
}

// KMP匹配：返回模式串在文本串中首次出现的起始索引，未找到返回-1
int kmpSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    if (m == 0) return 0;

    vector<int> next = getNext(pattern);
    int j = 0; // 模式串指针

    for (int i = 0; i < n; ++i) { // i是文本串指针
        // 匹配失败，根据next数组回退j
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1];
        }
        // 匹配成功，j前进
        if (text[i] == pattern[j]) {
            j++;
        }
        // 模式串完全匹配，返回起始索引
        if (j == m) {
            return i - m + 1;
        }
    }
    return -1; // 未找到
}
void test8(){
    string text = "ababcabcacbab";
        string pattern = "abcac";
        int index = kmpSearch(text, pattern);
        if (index != -1) {
            cout << "模式串在文本串中起始位置：" << index << endl; // 输出5
        } else {
            cout << "未找到模式串" << endl;
        }
}
int main(){
    //string s1 = "()[]{}";
    //cout << "测试用例1 \"" << s1 << "\": " << (isValid(s1) ? "有效" : "无效") << endl;
    //3 12abc-abCABc-4aB@
    //questionOne();
    //stringchar();
    //stringchar2();
    //test();
    //test2();
    //test3();//输入
    //test4();//字符串 Trim（去除首尾空格 / 特殊字符)
    //test5();//字符串压缩 / 解压缩
    //test6();//子序列 / 最长无重复子串
    test7();//多条件字符串校验
    test8();//kmp
    return 0;
}
