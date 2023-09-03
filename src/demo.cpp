#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <map>
#include "./socket/EventPoller.h"
#include "./socket/ServerSocket.h"
#include "./web/Server.h"
using namespace pisco::web;

#include "utility/Loger.h"
#include "utility/Json.h"
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

void StartServer()
{
    ZLOG::getInstance("./log/", "test.log", 1);

    Singleton<Server>::instance().Listen("", 5000);
    Singleton<Server>::instance().Bind("/Counter", CounterTest);
    Singleton<Server>::instance().Bind("/www/static/*", StaticHandler);
    
    Singleton<Server>::instance().Start();
}

int main() {

    StartServer();
  
    return 0;
}

