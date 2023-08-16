#pragma once
#include <memory>
#include "../utility/Timer.h"
using namespace pisco::utility;


namespace pisco
{
namespace thread
{
class Task
{

public:
    Task();
    Task(void * data);
    virtual ~Task(){};

    void setData(void * data){};
    void* getData();

    virtual void run() = 0;

protected:
    void * m_data_;
    std::shared_ptr<Counter> m_seq_;
};

}
}