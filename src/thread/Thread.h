#pragma once

#include <thread>
#include <string>
#include <iostream>
#include <sstream>

#include "../utility/Timer.h"
#include "../utility/Loger.h"
#include "../utility/SString.h"
using namespace pisco::utility;

namespace pisco{
namespace thread{

bool _SetThreadName(pthread_t thread_handle ,const std::string& name);

std::string _GetThreadName(pthread_t thread_handle);
using Handler = void (*)(void *);
enum kThreadStatus
{
    kReady = 0,
    kBusy,
    kIdel,
    kDel,
    kDone,
};

class Thread {
public:
    Thread() {}
    explicit Thread(std::thread t, const std::string& name = "")
            : m_thread(std::move(t))
            , m_name(name)
            {
                set_thread_Name(name);
            }

    //template<typename Callable>
    Thread(Handler f, const std::string& name)
        : m_name(name)
        , m_status(kReady)
    {
        m_thread = std::thread([=]() {
        f(this);
        });
    
        set_thread_Name(name);
        SetID();
        LOG_DEBUG("Create Worker:{}", m_name);
    }

    Thread(Thread&& other) noexcept
            : m_thread(std::move(other.m_thread))
            , m_name(std::move(other.m_name))
            , m_status(std::move(other.m_status))
            , m_threadId(std::move(m_threadId)){}

    ~Thread(){
        LOG_DEBUG("Release Worker:{}", m_name);
        ReleseRandomName(m_name);
    }

    Thread& operator=(Thread&& other) noexcept
    {
        if (this != &other)
        {
            m_thread = std::move(other.m_thread);
            m_name = std::move(other.m_name);
            m_status = std::move(other.m_status);
            m_threadId = std::move(m_threadId);
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

    void SetID()
    {
        std::ostringstream oss;
        oss << m_thread.get_id();
        m_threadId = oss.str();
    }

    std::string get_id() const
    {
        return m_threadId;
    }

    bool set_thread_Name(const std::string &name);
    
    std::string get_thread_name();

    kThreadStatus GetStatus(){return m_status;};

    void SetStatus(kThreadStatus status){m_status = status;};

    void UpdateIdelTime(){
        m_start_time = std::chrono::steady_clock::now();
    };

    bool IsLasyTooLong(){
        auto duration = (std::chrono::steady_clock::now() - m_start_time);
        return (std::chrono::duration<double>(duration).count() > 30);
    };
    
private:
    std::thread m_thread;
    std::string m_threadId;
    std::string m_name;
    kThreadStatus m_status;
    std::chrono::steady_clock::time_point m_start_time;
};

}
}


