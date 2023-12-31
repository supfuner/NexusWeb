#include "../socket/SocketHandler.h"
using namespace pisco::socket;

#include "Server.h"
using namespace pisco::web;

#include "../utility/Config.h"
#include "../utility/SString.h"
using namespace pisco::utility;

#include "../control/ClassFactory.h"
using namespace pisco::control;

Server::Server():m_ip(""),m_port(5001)
{
    Route::GetRouteFromfile(m_handlers);   
}

Server::~Server()
{

}

void Server::Listen(const string &ip, int port)
{
    m_ip = ip;
    m_port = port;
}

void Server::Bind(const string & path, server_handler handler)
{
    m_function_handlers.insert(std::pair<string, server_handler>(path, handler));
}

void Server::Start()
{
    pisco::utility::Singleton<SocketHandler>::instance().listen(m_ip, m_port);
    LOG_INFO("************NexusWeb************");
    LOG_INFO("*Server:{} Port:{}", m_ip, m_port);
    LOG_INFO("*------------Route-------------*");
    for(auto iter = m_handlers.begin(); iter != m_handlers.end(); iter++) {
        LOG_INFO("*Path:{}, Control:{}*",iter->first,iter->second);
    } 
    LOG_INFO("*******************************");   
    pisco::utility::Singleton<SocketHandler>::instance().handle(1000, 10000);
}

string Server::Handle(const Request & req)
{
    const string & path = req.path();
    CustomFinder finder(path);
    auto func = std::find_if(m_function_handlers.begin(), m_function_handlers.end(), finder);
    //auto func = m_function_handlers.find(path);
    Response resp;
    if(func != m_function_handlers.end()){
       
        func->second(req, resp);
        return resp.data();
    }
    else
    {   auto ctl = m_handlers.find(path);
        if(ctl != m_handlers.end())
        {
            vector<string> output;
            SString::split(output, ctl->second, ".");
            shared_ptr<BaseControl> b =  Singleton<ClassFactory>::instance().CreateControl(output[0]);
            if (b != nullptr)
            {
                b->exec(output[1], req, resp);
                return resp.data();
            }
            LOG_WARN("Path[{}]Unregister class[{}][{}]", output[0], output[1]);
        }
        return resp.page_not_found();
    }
    
}

void Server::test()
{
    std::map<string, string> handlers;
    Route::GetRouteFromfile(handlers);
}