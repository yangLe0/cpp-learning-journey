//
//  thread_para.cpp
//  test
//
//  Created by 天塌不惊 on 2025/12/10.
//  编码标准：成员函数首字母大写，成员小写字母，私有成员后面加一个杠，私有成员对外开放时候的成员函数也是小写只是少一个杠

#include <thread>
#include <iostream>
#include <string>
//Linux -lpthread
using namespace std;
class MyThread
{
public:
    //入口线程函数
    void Main()
    {
        cout << "MyThread Main "<<name<<":"<<age;
    }
    string name = "";
    int age = 100;
};
class XThread//把XThread放到一个头文件
{
public:
    virtual void Start()//线程的启动在基类当中
    {
        is_exit_ = false;
        th_ = std::thread(&XThread::Main,this);//如果做一个公共的XThread库，不把命名空间引进来，防止冲突
    }
    virtual void Stop()//让线程主动退出
    {
        is_exit_ = true;
        Wait();
    }
    virtual void Wait()
    {
        if(th_.joinable())//判断有可能是不能join的，比如对象已经被清理掉了，就是线程id号没有了
            th_.join();
    }
    bool is_exit(){return is_exit_;}//给外部调用
private:
    virtual void Main() = 0;//只做声明不实现，约定继承者必须实现
    std::thread th_;
    bool is_exit_ = false;
};
class TestXThread:public XThread
{
public:
    void Main() override//入口函数希望在派生类当中，加override在编译阶段就能解决有没有写错函数名字的问题，重载父类有没有这个函数
    {
        
        cout <<"TestXThread Main begin"<<endl;
        while(!is_exit())
        {
            this_thread::sleep_for(100ms);
            cout <<"."<<flush;//加个刷新，确保这个点.显示，屏幕输出的话在线程当中这个点会先输出到标准输出的缓冲当中不会立刻显示
        }
        cout <<"TestXThread Main end"<<endl;

    }
    string name;
};
int main(int argc, char* argv[])
{
    TestXThread testth;
    testth.name="testXThread name";
    testth.Start();
    this_thread::sleep_for(3s);
    testth.Stop();
    testth.Wait();//等待它的退出
    getchar();
    
    MyThread myth;
    myth.name = "test name 001";
    myth.age = 20;
    thread th(&MyThread::Main,&myth);//传递成员函数的指针，通过对象的地址访问
    th.join();
    return 0;
}
