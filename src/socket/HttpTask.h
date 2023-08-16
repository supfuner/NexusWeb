#pragma once

#include "../thread/Task.h"
using namespace pisco::thread;

namespace pisco{
namespace socket{

class HttpTask : public Task
{
public:
    HttpTask(void * data) : Task(data){};
    virtual void run() override;

};
}
}