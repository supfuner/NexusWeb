#include "ThreadPool.h"
using namespace pisco::thread;

#include "../utility/Config.h"
#include "../utility/Loger.h"
using namespace pisco::utility;



ThreadPool::ThreadPool(const size_t &threadCount)
    : max_threadSize_(threadCount)
    , m_stop(false)
{
    /***********read config**********/
    m_config_param_["threadPool.init_thread_num"] = "";
    bool ret = Ini::readConfig("../config/pisTPconfig.ini", m_config_param_);
    int core_num = atoi(m_config_param_["threadPool.core_thread"].c_str());
    core_num = (core_num <= 0) ? init_thread_size : core_num;
    LOG_DEBUG("************ThreadPool************");
    LOG_DEBUG("*MaxiThreadSize:{}*", max_threadSize_);
    LOG_DEBUG("*CoreThreadSize:{}*", core_num);
    LOG_DEBUG("*******************************");
    addThreads(core_num);
}

// 析构函数，等待所有线程完成任务后退出
ThreadPool::~ThreadPool()
{
    m_stop = true;
    m_condition.notify_all();
    for (auto& thread : m_threads) {
        thread.join();
    }
}

void ThreadPool::addThreads(uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        addThread();
  }  
}

void ThreadPool::addThread(const std::string & name)
{
    std::lock_guard<std::mutex> lock(m_threadsMutex);

    m_threads.emplace_back([this, name]{
        while (!m_stop.load())
        {            
            std::shared_ptr<Task> task = nullptr;
            std::thread::id this_thread_id;
            {
                std::unique_lock<std::mutex> lock(m_queueMutex);                
                m_threads_status[std::this_thread::get_id()] = {true, std::chrono::steady_clock::now(), false};
                m_condition.wait(lock, [this]{ return m_stop || !m_tasks.empty();});
                if(IsExpired())
                {
                    return;
                }

                if (m_stop && m_tasks.empty())
                {
                    return;
                }
                this_thread_id = std::this_thread::get_id();
                task = std::move(m_tasks.front());
                m_tasks.pop();
                m_threads_status.erase(std::this_thread::get_id());
            }
            {
                Timer t(&task);
                task->run();
            }
        }
            
    }, name);
}

void ThreadPool::addMonitor(const std::string &name)
{
        // m_threads.emplace_back([this]{
        //     while (!m_stop.load())
        //     {

        //         for (auto i : m_runnig_tasks_)
        //         {
        //             auto d = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - i.second);
        //             if(d > std::chrono::seconds(10)){
        //                 //std::cout<<"time out"<<i.first<<"::"<<d.count()<<"\n";
        //             }
                    
        //         }                
        //         std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        //     }
        // }, name);
}

void ThreadPool::addTask(std::shared_ptr<Task> task)
{
    std::unique_lock<std::mutex> lock(m_queueMutex);     
    m_tasks.push(task);
    ManageThreads();
    LOG_INFO("**total[{}],busy[{}],idle[{}],taskLeft[{}]", m_threads.size(), (m_threads.size()-m_threads_status.size()),
    m_threads_status.size(), m_tasks.size());

}

void ThreadPool::ManageThreads()
{
    if(m_threads_status.size() > 0 && m_threads.size() >= 1) {
        for(auto &it : m_threads_status){
            auto duration = std::chrono::steady_clock::now() - it.second.keepAliveTime;
            auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
            std::cout<<"threadID:"<<it.first<<"\t time:"<<seconds.count()<<std::endl;
            if (seconds.count() > 120)
            {
                it.second.isNeedDelete = true;
            }
        }
        m_condition.notify_all();        
    }
    else {
        //int addNum = (max_threadSize_ > m_tasks.size()) ? m_tasks.size() : max_threadSize_;
        //addThreads(addNum);
        m_condition.notify_one();
    }
}

bool ThreadPool::IsExpired()
{
    auto threadStatus = m_threads_status.find(std::this_thread::get_id());
    if (threadStatus != m_threads_status.end())
    {
        if (threadStatus->second.isNeedDelete)
        {
            m_threads_status.erase(std::this_thread::get_id());
            std::cout<<"**end thread:"<<std::this_thread::get_id()<<std::endl;
            return true;
        }                    
    }
    return false;
}