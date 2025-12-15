//
//  thread_msg_server.cpp
//  test
//
//  Created by 天塌不惊 on 2025/12/15.
//

#include "xmsg_server.hpp"
#include <sstream>
using namespace std;
int main(int argc, char* argv[])
{
    XMsgServer server;
    server.Start();
    for (int i=0; i<10; i++)
    {
        stringstream ss;
        ss<<" msg: "<<i+1;
        server.SendMsg(ss.str());
        this_thread::sleep_for(500ms);
    }
    server.Stop();
    
    return 0;
}

