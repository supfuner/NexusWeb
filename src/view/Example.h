#pragma once

#include <string>
#include "../control/BaseControl.h"
using namespace pisco::control;

namespace pisco{
namespace view{
    class Example : public BaseControl
    {
    public:
        Example(){};
        virtual ~Example() override;
        void TestAjax(const Request &, Response &);
        // void test();
    };
}
}