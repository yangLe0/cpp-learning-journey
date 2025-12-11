//
//  thread_RAII.cpp
//  test
//
//  Created by 天塌不惊 on 2025/12/11.
//

#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <shared_mutex>
//Linux -lpthread
using namespace std;
//RAII
class XMutex
{
public:
    XMutex(mutex &mux):mux_(mux)
    {
        cout<<"Lock"<<endl;
        mux.lock();
    }
    ~XMutex()
    {
        cout<<"Unlock"<<endl;
        mux_.unlock();
    }
private:
    mutex& mux_;//引用需要在初始化的时候赋值
};
static mutex mux;
void TestMutex(int status)
{
    XMutex lock(mux);//不用管它的释放了
    if (status == 1) {
        cout <<"=1"<<endl;
        return;
    }
    else
    {
        cout <<"!=1"<<endl;
        return;
    }
}
int main(int argc, char* argv[])
{
    TestMutex(1);
    TestMutex(2);
    getchar();
    return 0;
}
