#pragma once

#include <string>
#include "../control/BaseControl.h"
using namespace pisco::control;

namespace pisco{
namespace view{
    class Index : public BaseControl
    {
    public:
        Index(){};
        virtual ~Index() override;
        void show(const Request &, Response &);
        void test(const Request & req, Response & resp);
    };
}
}
