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
static mutex gmutex;
void TestLockGuard(int i)
{
    gmutex.lock();
    {
        //已经拥有锁，不能lock
        //lock_guard<mutex> lock(gmutex);//有lock
        lock_guard<mutex> lock(gmutex, adopt_lock);//带个参数没有lock
        //结束释放锁
    }
    {
        lock_guard<mutex> lock(gmutex);
        cout<<"begin thread"<<i<<endl;
    }
    
    
    for(;;)
    {
        {
            lock_guard<mutex> lock(gmutex);
            cout<<"In "<<i<<endl;
        }
        this_thread::sleep_for(500ms);
    }
}
int main(int argc, char* argv[])
{
    for(int i=0;i<3;i++)
    {
        thread th(TestLockGuard,i+1);
        th.detach();
    }
    TestMutex(1);
    TestMutex(2);
    getchar();
    return 0;
}
