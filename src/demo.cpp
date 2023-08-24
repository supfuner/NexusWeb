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
    Singleton<Server>::instance().Start();
}



#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace boost::property_tree;

void processValue(const ptree& node) {
    // 判断值的类型
    if (node.empty()) {
        // 值为空，可能是 null
        std::cout << "Value: null" << std::endl;
    } else if (node.count("") > 0) {
        // 值是数组
        for (const auto& child : node) {
            std::cout << "Array item: " << child.second.data() << std::endl;
        }
    } else {
        // 值是对象或是基本类型
        std::cout << "Value: " << node.data() << std::endl;
    }
}


int main1() {
    std::string jsonString = R"({"array": [1, 2, 3], "value": "Hello", "object": {"key": "value"}})";
    return 0;
}

int main() {

    StartServer();
  
    return 0;
}

