
#include "HttpTask.h"
#include "SocketHandler.h"
using namespace pisco::socket;

#include "../utility/Loger.h"
#include "../utility/Singleton.h"
using namespace pisco::utility;

#include "../web/Request.h"
#include "../web/Server.h"
using namespace pisco::web;

#include "Socket.h"
const int kRecvBufferSize = 1024;

void HttpTask::run()
{ 
    Socket * socket = static_cast<Socket *>(m_data_);
    char buffer[kRecvBufferSize] = {0};
    int len = socket->recv(buffer, kRecvBufferSize);
    if (len > 0)
    {
        LOG_DEBUG("len :{}, data:{}", len, buffer);
        Request req;
        req.parse(buffer, len);
        string output = Singleton<Server>::instance().Handle(req);
        socket->send(output.c_str(), output.size());
        Singleton<SocketHandler>::instance().attach(socket);
    }
    else
    {
        Singleton<SocketHandler>::instance().remove(socket);
    }
    // 模拟任务执行时间    
}