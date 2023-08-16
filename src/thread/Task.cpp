#include "Task.h"


using namespace pisco::thread;

Task::Task()
{
    m_seq_ = std::make_shared<Counter>();
    m_data_ = nullptr;
}

Task::Task(void * data):Task()
{
    m_data_ = data;
}

void * Task::getData()
{
    return m_data_;
}


