#pragma once

#include <string>
#include "../control/BaseControl.h"
using namespace pisco::control;

namespace pisco{
namespace view{
    class Admin : public BaseControl
    {
    public:
        Admin(){};
        virtual ~Admin() override;
        void Index(const Request &, Response &);
        void test();
    };
}
}
