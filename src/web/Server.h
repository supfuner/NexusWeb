#pragma once

#include <functional>
#include <string>
using namespace std;

#include "../utility/Singleton.h"
#include "Response.h"
#include "Request.h"

namespace pisco{
namespace web{

typedef std::function<void(const Request &, Response &)> server_handler;

class Server
{
    friend class pisco::utility::Singleton<Server>;
    
public:
    void Listen(const std::string &ip, int port);
    void Start();
    void Bind(const string & path, server_handler handler);
    string Handle(const Request & req);
    void test();
    Server();
    ~Server();
    
private:
    std::string m_ip;
    int m_port;
    std::map<string, server_handler> m_function_handlers;
    std::map<string, string> m_handlers;
};
    
}
}
