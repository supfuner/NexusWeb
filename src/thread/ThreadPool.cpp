#include "ThreadPool.h"
using namespace pisco::thread;

#include "../utility/Config.h"
#include "../utility/Loger.h"
#include "../utility/SString.h"
using namespace pisco::utility;
bool condition = false;
bool IsConditionSatisfied() {
    return condition;
}
void Worker(void * userData)
{
    Thread * user = static_cast<Thread *>(userData);
    while (!Singleton<ThreadPool>::instance().CheckStatus() && nullptr != user)
    {  
        user->UpdateIdelTime();        
        if (kDel == user->GetStatus())
        {
            break;
        }        
        user->SetStatus(kIdel);
        std::shared_ptr<Task> task = nullptr;
        std::thread::id this_thread_id;
        {
            std::unique_lock<std::mutex> lock(Singleton<ThreadPool>::instance().m_queueMutex);
            Singleton<ThreadPool>::instance().m_condition.wait(lock, [=]{ return Singleton<ThreadPool>::instance().CheckTaskStatus()|| (kDel==user->GetStatus());});
            if (kDel == user->GetStatus())
            {
                break;
            }  
            task = Singleton<ThreadPool>::instance().GetTask();
            if(nullptr == task){ return;}
        }
        {
            user->SetStatus(kBusy);
            Timer t(&task);
            task->run();
        }
    } 
};

void Manager(void * userData)
{
    while (!Singleton<ThreadPool>::instance().CheckStatus())
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        Singleton<ThreadPool>::instance().ManageThreads();
    }   
}


ThreadPool::ThreadPool(const size_t &threadCount)
    : max_threadSize_(threadCount)
    , m_stop(false)
{
    /***********read config**********/
    m_config_param_["threadPool.init_thread_num"] = "";
    bool ret = Ini::readConfig("../config/pisTPconfig.ini", m_config_param_);
    m_core_thread_num = atoi(m_config_param_["threadPool.core_thread"].c_str());
    m_core_thread_num = (m_core_thread_num <= 0) ? init_thread_size : m_core_thread_num;
    LOG_DEBUG("************ThreadPool************");
    LOG_DEBUG("*MaxiThreadSize:{}*", max_threadSize_);
    LOG_DEBUG("*CoreThreadSize:{}*", m_core_thread_num);
    LOG_DEBUG("*******************************");

    m_manager = std::make_shared<Thread>(Manager, "Manager");
    AddThreads(5);
}

// 析构函数，等待所有线程完成任务后退出
ThreadPool::~ThreadPool()
{
    m_stop = true;
    m_condition.notify_all();
    for (auto& thread : m_threads) {
        thread.second->join();
    }
}

void ThreadPool::AddThreads(uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        AddThread();
  }  
}

void ThreadPool::AddThread(const std::string & name)
{
    std::lock_guard<std::mutex> lock(m_threadsMutex);
    std::string threadName = GetRandomName();
    std::shared_ptr<Thread>  t = std::make_shared<Thread>(Worker, threadName);
    std::string threadId = t->get_id();
    m_threads[threadId] = std::move(t);
    LOG_DEBUG("**add threadName[{}],threadID[{}], thread size[{}]", threadName, threadId, m_threads.size());
}

void ThreadPool::DelThread(const std::string& threadId)
{
    std::lock_guard<std::mutex> lock(m_threadsMutex);
    auto thread = m_threads.find(threadId);
    std::string threadName;
    if (thread != m_threads.end())
    {
        thread->second->SetStatus(kDel);
        threadName = thread->second->get_thread_name();     
        m_threads.erase(threadId); 
    }
    else
     
    LOG_DEBUG("**del threadName[{}], thread[{}], thread size[{}]", threadName, threadId, m_threads.size());
}

void ThreadPool::AddTask(std::shared_ptr<Task> task)
{
    std::unique_lock<std::mutex> lock(m_queueMutex);     
    m_tasks.push(task);        
    LOG_DEBUG("**total[{}],busy[{}],taskLeft[{}]", m_threads.size(), (m_busy_num), m_tasks.size());
    m_condition.notify_one();
}

std::shared_ptr<Task> ThreadPool::GetTask()
{
    //std::unique_lock<std::mutex> lock(m_queueMutex);
    if (m_stop && m_tasks.empty())
    {
        return nullptr;
    }
    std::shared_ptr<Task> task = std::move(m_tasks.front()); 
    m_tasks.pop();
    return task;
}

void ThreadPool::ManageThreads()
{
    std::vector<std::string> idelVec;
    int busyNum = 0;
    for (auto it = m_threads.begin(); it != m_threads.end(); ) 
    {
        if (kDel == it->second->GetStatus()) {
            auto next_it = std::next(it);
            it->second->join();
            DelThread(it->second->get_id());
            it = next_it;
        }
        else if (kIdel == it->second->GetStatus() && it->second->IsLasyTooLong())
        { 
           idelVec.push_back(it->first);
            ++it;
        }
        else
        {
            ++it;
            busyNum++;
        }        
    }
    m_busy_num = busyNum;
    int totalNum = m_threads.size();
    int taskNum = m_tasks.size() ;
    if (taskNum <= idelVec.size())
    {
        for (size_t i = 0; i < idelVec.size() && totalNum > m_core_thread_num; i++)
        {
            m_threads[idelVec[i]]->SetStatus(kDel);
            totalNum--;
        }        
    }
    else
    {        
        int num = (m_tasks.size() - idelVec.size()) > (max_threadSize_ - m_threads.size()) ? (max_threadSize_ - m_threads.size()) \
            : (m_tasks.size() - idelVec.size());
        AddThreads(num);
    }
    m_condition.notify_all();
}
