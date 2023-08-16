#pragma once
#include <iostream>
#include <chrono>
#include <string>
using namespace std;

namespace pisco{
namespace utility{
class Timer{

public:
    Timer(void * id = nullptr):
    m_start_time_(std::chrono::steady_clock::now()),
    m_id_(id)
    {

    }
    ~Timer(){}
    std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - m_start_time_;
private:
    std::chrono::steady_clock::time_point m_start_time_;
    void *m_id_;
};

class Counter
{
public:
    Counter(){};
    ~Counter(){};
    
    time_t GetCounter(){return m_count_++;};
    
private:

    time_t m_count_;
};

}
}