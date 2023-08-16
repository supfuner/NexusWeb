#include <iostream>
#include "threadPool.h"

using namespace PISCO::Core;



void task1(){
    char name[24];
    pthread_getname_np(pthread_self(), name, 16);
    int i = 0;
    while(i++ < 100){
        std::cout<<name<<"-"<<pthread_self()<<" excute task1"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 休眠500毫秒
    }
   
}

void task2(int n){
    char name[24];
    pthread_getname_np(pthread_self(), name, 16);
    std::cout<<name<<"-"<<pthread_self()<<" excute task2=="<<n<<std::endl;
}

int task3(){
    char name[24];
    pthread_getname_np(pthread_self(), name, 16);
    std::cout<<name<<"-"<<pthread_self()<<" excute task3"<<std::endl;
    return 8;
}



int main() {
    PISCO::Core::ThreadPool * p = new PISCO::Core::ThreadPool();
    
    std::future<void> ff = p->addTask(task1);
    std::future<void> f =  p->addTask(task2,0);
    std::future<int> f1 =  p->addTask(task3);



    while (true){
        std::this_thread::sleep_for(std::chrono::milliseconds(5000)); // 休眠500毫秒
    }
    
    
    return 0;
}
