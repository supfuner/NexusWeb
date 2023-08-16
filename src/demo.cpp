#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "./socket/EventPoller.h"
#include "./socket/ServerSocket.h"
#include "./web/Server.h"
using namespace pisco::web;

#include "utility/Loger.h"
#include "./socket/HttpTask.h"
#include "./thread/Task.h"
//using namespace pisco::server;
using namespace pisco::socket;
using namespace pisco::utility;
using namespace std;

#include "./control/ControlHandler.h"



#define  SOCKET_PORT 5000
#define MAX_LISTEN_SOCKET 10


class A {
    public:
    A(int n){
        std::cout<<"create"<<std::endl;
        a = n;
    }
    ~A(){
        std::cout<<"decreate"<<std::endl;
    }
    int a;
};

std::vector<A> m;



void func()
{
    for (size_t i = 0; i < 20; i++)
    {
        m.emplace_back(10);
    }  
    
};
int main() {

    ZLOG::getInstance("./log/", "test.log", 2);
    Server * m_server = Singleton<Server>::instance();
    m_server->Listen("", 5000);
    m_server->Bind("/Counter", CounterTest);
    m_server->Start();
    
    return 0;
}

