#pragma once

#include <memory>
#include "../socket/Socket.h"
using namespace pisco::socket;

#include "Task.h"
//using namespace yazi::thread;

#include "../socket/HttpTask.h"
using namespace pisco::socket;

namespace pisco {
namespace thread {
enum TaskType
{
    kHttpTask = 0,
    kOtherTask,
};

class TaskFactory
{
public:
    static std::shared_ptr<Task> create(void * socket, TaskType type = kHttpTask)
    {
        switch (type)
        {
        case kHttpTask:
            return std::make_shared<HttpTask>(socket);
            break;
        
        default:
            break;
        }
        return nullptr;
    }
};

}
}