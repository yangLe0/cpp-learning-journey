//
//  thread_mutex.cpp
//  test
//
//  Created by 天塌不惊 on 2025/12/11.
//

#include "thread"
#include <iostream>
#include <string>
#include <mutex>
//Linux -lpthread
using namespace std;
static mutex mux; //互斥变量
void TestThread()
{
    for(;;)
    {
        //获取锁资源，如果没有则阻塞等待
        //mux.lock();//操作系统层面的锁，只能有一个线程进入，这段代码称为临界区，保证临界区尽可能小，尽量晚锁
        if(!mux.try_lock())//尝试去锁，没有获取到锁也做一些处理，监控到获取锁的过程，这行代码有开销
        {//返回true是获取到锁了
            cout<<"."<<flush;
            this_thread::sleep_for(100ms);//每100ms去试图获取到锁，加这行给资源释放
            continue;
        }
        cout << "===================" << endl;
        cout << "test 001" << endl;
        cout << "test 002" << endl;
        cout << "test 003" << endl;
        cout << "===================" << endl;
        mux.unlock();//尽量早释放锁
        this_thread::sleep_for(1000ms);
    }
}
void ThreadMainMux(int i)
{
    for(;;)
    {
        mux.lock();
        cout<<i<<"[in]"<<endl;
        this_thread::sleep_for(1000ms);
        mux.unlock();//unlock到lock之间可能是微秒级别的，同一个线程unlock之后马上lock一直占着资源
        this_thread::sleep_for(1ms);//留一点时间释放，让操作系统真的把资源释放掉，让排队线程交替处理
    }
}
timed_mutex tmux;//支持超时的互斥锁
void ThreadMainTime(int i)
{
    for(;;)
    {
        if(!tmux.try_lock_for(chrono::milliseconds(600)))//超时多长时间500毫秒
        {
            cout <<i<<"[try_lock_for timeout]"<<endl;
            continue;
        }
        cout <<i<<"[in]"<<endl;
        this_thread::sleep_for(2000ms);
        tmux.unlock();
        this_thread::sleep_for(1ms);
    }
}
int main(int argc, char* argv[])
{
    for(int i=0;i<3;i++)
    {
        thread th(ThreadMainTime,i+1);
        th.detach();
    }
    getchar();
    for(int i=0;i<3;i++)
    {
        thread th(ThreadMainMux,i+1);
        th.detach();
    }
    getchar();
    for(int i=0; i<10;i++)
    {
        thread th(TestThread);
        th.detach();
    }
    getchar();
}
