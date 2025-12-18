//
//  threequestions.cpp
//  test
// 1**牛牛与切割机**
// 有一个序列 a1,a2,...,an*a*1,*a*2,...,*an* ， 牛牛将对这个序列切割一刀（划分分成两个不相交的非空序列，一个序列为 a1,…,ap*a*1,…,*ap*，另一个序列为 ap+1,…,an*ap*+1,…,*an*），牛牛切割的代价为两个序列元素和的乘积。牛牛想知道切割代价最小是多少。
// 2**字符串排序**
//给定 n*n* 个字符串，请你对这 n*n* 个字符串按照以下规则从小到大排序。对于任意两个字符串 s*s* 和 t*t* ，在排序后应当满足：- 若 s*s* 是 t*t* 的一个前缀，则 s*s* 在排序后的下标小于等于 t*t* 的在排序后的下标。- 若存在整数 i*i* ，使得 s*s* 的前 i−1*i*−1 个字符和 t*t* 的前 i−1*i*−1 个字符相同，且 s*s* 和 t*t* 的第 i*i* 个字符不同，则比较第 i*i* 个字符的大小关系（字符的大小关系顺序由输入数据给出）。若 s*s* 的第 i*i* 个字符小于等于 t*t* 的第 i*i* 个字符，则 s*s* 在排序后的下标小于等于 t*t* 的在排序后的下标。容易发现，上述排序方法的排序结果是唯一的。
// 3**牛牛的糖果树**
//牛牛的朋友送了她一棵节点数为 n*n*的糖果树（1号点为根节点），树上的每个糖果都有一个颜色。
//牛牛吃糖果有一个习惯，她每次都会吃掉一整个子树的糖果，她喜欢与众不同，所以每次吃之前她都会把出现次数最多的颜色的糖果扔掉（可能有多个出现次数最多的颜色，此时要全部扔掉），她可以选择任意一棵子树吃掉，但她只能吃一次，因此他想知道她一次能吃到的所有糖果的颜色的异或和最大是多少（如果吃到了多个颜色相同的糖果，也需要做多次异或），你能帮帮她吗？
//  Created by 天塌不惊 on 2025/12/18.
//

#include <stdio.h>
#include <vector>
#include <iostream>
#include <climits>
#include <map>
using namespace std;
void firstone()
{
    int n;
    cin >> n;
    vector<int> numbers(n);
    int total=0,presum=0;
    long long cost,mincost=LLONG_MAX;//notice
    for(int i=0; i<n;i++)
    {
        int a;
        cin >> a;
        numbers.push_back(a);
        total+=a;
    }
    for(int i=0;i<n-1;i++)
    {
        presum += numbers[i];
        cost = presum * (total-presum);
        //cout << "cost:"<<cost<<endl;
        if(cost < mincost)
        {
            mincost = cost;
        }
    }
    cout << mincost <<endl;
}
unordered_map<char, int> ruin_map;
bool compare(const string& s,const string& t)
{
    int min_len = min(s.size(),t.size());
    cout <<"s:"<<s<<" t:"<<t<<" min_len:"<<min_len<<endl;
    for(int i=0;i<min_len;i++)
    {
        if (s[i]!=t[i]) {//notice
            return ruin_map[s[i]] < ruin_map[t[i]];//notice
        }
    }
    return s.size() < t.size();//notice
}
void secondone()
{
    int n;
    string mark;
    cin >> n >> mark;
    vector<string> strlist(n);
    
    for(int i=0;i<n;i++)
    {
        cin >> strlist[i];
    }
    for(int i=0;i<mark.size();i++)
    {
        ruin_map[mark[i]]=i;
    }
    sort(strlist.begin(),strlist.end(),compare);
    for(const auto&ele:strlist)
    {
        cout << ele << endl;
    }
}
int main()
{
    //firstone();
    //second();
    
    return 0;
}
