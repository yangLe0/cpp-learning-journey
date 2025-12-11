//
//  thread_lambda.cpp
//  test
//
//  Created by 天塌不惊 on 2025/12/11.
//

#include <thread>
#include <iostream>
#include <string>
//Linux -lpthread
using namespace std;
class TestLambda
{
public:
    void Start()
    {
        thread th([this](){cout<<"name="<<name<<endl;});//捕获成员需要this指针
        th.join();
    }
    string name = "test lambda";
};
int main(int argc, char* argv[])
{
    thread th([](int i){cout<<"test lambda " << i <<endl;}, 123);
    th.join();
    TestLambda testlam;
    testlam.Start();
}
