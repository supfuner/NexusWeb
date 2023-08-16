#pragma once

#include <atomic>
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>
#include <future>
#include <type_traits>
#include <map>
#include "Task.h"
#include "Thread.h"
#include "../utility/Singleton.h"


namespace pisco{

namespace thread{

const int init_thread_size = 5;

struct IdelInfo
{
    bool isIdel;
    std::chrono::steady_clock::time_point keepAliveTime;
    bool isNeedDelete;
};


class ThreadPool : public Thread{

    friend class pisco::utility::Singleton<ThreadPool>;

public:
    // 禁用拷贝和移动构造函数
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    //void printfThreadInfo();
    void addMonitor(const std::string &name);
    void addTask(std::shared_ptr<Task> task);

private:
    // 构造函数，初始化线程池
    explicit ThreadPool(const size_t &threadCount = std::thread::hardware_concurrency()); 
    ~ThreadPool();  // 析构函数，等待所有线程完成任务后退出

private:
    void addThread(const std::string &name="pisco_worker");
    void addThreads(uint32_t n = init_thread_size);
    void getIdleThread();
    void ManageThreads();
    bool IsExpired();

private:
    std::vector<Thread> m_threads;                      // 线程池中的所有线程队列
    std::queue<std::shared_ptr<Task>> m_tasks;          // 任务队列
    std::atomic_bool m_stop;                            // 是否退出标志
    std::mutex m_queueMutex;                            // 任务队列的互斥锁
    std::mutex m_threadsMutex;                          // 任务队列的互斥锁
    std::condition_variable m_condition;                // 条件变量，用于等待任务队列中是否有待执行的任务
    size_t max_threadSize_;                             // 最大允许开辟的线程数
    std::map<std::thread::id, std::chrono::time_point<std::chrono::high_resolution_clock>> m_runnig_tasks_;
    std::map<std::string, std::string> m_config_param_;
    std::map<std::thread::id, IdelInfo> m_threads_status;
};

}
}
