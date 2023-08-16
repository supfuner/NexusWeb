#pragma once

#include <thread>
#include <string>
#include <iostream>

#include "../utility/Timer.h"
//#include "Loger.h"

namespace pisco{
namespace thread{

bool _SetThreadName(pthread_t thread_handle ,const std::string& name);

std::string _GetThreadName(pthread_t thread_handle);

//time_t _GetTimestamp();

class Thread {
public:
    Thread() {}
    explicit Thread(std::thread t, const std::string& name = "")
            : m_thread(std::move(t))
            , m_name(name)
            {
                set_thread_Name(name);
            }

    template<typename Callable>
    Thread(Callable&& f, const std::string& name)
    {
        m_thread = std::thread([=]() {
        f();
        });
    
        set_thread_Name(name);
    }

    Thread(Thread&& other) noexcept
            : m_thread(std::move(other.m_thread))
            , m_name(std::move(other.m_name)){}

    ~Thread(){
        std::cout<<"decreate:"<<std::this_thread::get_id()<<std::endl;
    }

    Thread& operator=(Thread&& other) noexcept
    {
        if (this != &other)
        {
            m_thread = std::move(other.m_thread);
            m_name = std::move(other.m_name);
        }
        return *this;
    }

    void join()
    {
        m_thread.join();
    }

    void detach()
    {
        m_thread.detach();
    }

    std::thread::id get_id() const
    {
        return m_thread.get_id();
    }

    bool set_thread_Name(const std::string &name);
    
    std::string get_thread_name();
private:
    std::thread m_thread;
    std::string m_name;
    
};

}
}


