//
//  xmsg_server.hpp
//  test
//
//  Created by 天塌不惊 on 2025/12/15.
//

#ifndef xmsg_server_hpp
#define xmsg_server_hpp

#include "xthread.hpp"
#include <string>
#include <list>
#include <mutex>
class XMsgServer : public XThread
{
public:
    //给当前线程发消息
    void SendMsg(std::string msg);
private:
    //处理消息的线程入口函数
    void Main() override;
    
    //消息队列缓冲
    std::list<std::string> msgs_;
    
    //互斥访问消息队列
    std::mutex mux_;
};

#endif /* xmsg_server_hpp */
