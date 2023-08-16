#pragma once

#include <list>
using std::list;

#include <string>
using std::string;

#include "Socket.h"
#include "EventPoller.h"
#include "../utility/ObjectPool.h"
#include "../utility/Loger.h"
using namespace pisco::utility;

namespace pisco{
namespace socket{
class SocketHandler
{    
public:
    SocketHandler();
    ~SocketHandler();

    void listen(const string & ip, int port);
    void attach(Socket * socket);
    void detach(Socket * socket);
    void remove(Socket * socket);
    void handle(int max_connections, int wait_time);

private:
    EventPoller * m_epoll;
    Socket * m_server;
    ObjectPool<Socket> m_sockpool;
    //Mutex m_mutex;
};
}
}


