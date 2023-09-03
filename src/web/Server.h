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

struct CustomFinder {
    std::string key;

    CustomFinder(const std::string& k) : key(k) {}

    bool operator() (const std::pair<std::string, server_handler>& pair) const {
        int ret = false;
        std::string pairKey = pair.first;
        if (pairKey == key)
        {
            ret = true;
        }
        else if (pairKey.find("*") != std::string::npos && key.size() > 2)
        {
            auto pos = pairKey.find("*");
            if (key.find(pairKey.substr(0, pos)) != std::string::npos)
            {
                ret = true;
            }            
        }
        else
        {
            ret = false;
        }
        return ret;
    }
};

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
