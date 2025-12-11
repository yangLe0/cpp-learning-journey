//
//  thread_shared.cpp
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
//c++17
//shared_mutex smux;

//c++14
shared_timed_mutex stmux;

void ThreadRead(int i)
{
    for(;;)
    {
        stmux.lock_shared();
        cout <<i<<" Read"<<endl;//读线程的入口函数和处理
        this_thread::sleep_for(500ms);
        stmux.unlock_shared();
        this_thread::sleep_for(1ms);
    }
}
void ThreadWrite(int i)
{
    for(;;)//要不要读数据需要逻辑判断
    {
        stmux.lock_shared();//只要没有人锁定互斥锁，共享锁都是立刻返回的
        //读取数据
        stmux.unlock_shared();
        stmux.lock();//互斥锁 写入，只要有人锁定互斥锁，所有共享锁都不能进，其他互斥锁也不能进
        cout<<i<<" Write" <<endl;
        this_thread::sleep_for(300ms);
        stmux.unlock();
        this_thread::sleep_for(1ms);
    }
}
int main(int argc, char* argv[])
{
    for(int i=0; i<3;i++)
    {
        thread th(ThreadWrite, i+1);
        th.detach();
    }
    for(int i=0; i<3;i++)
    {
        thread th(ThreadRead, i+1);
        th.detach();
    }
    getchar();
    return 0;
}
