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
        void Login(const Request &, Response &);
        void Index(const Request &, Response &);
        void Content(const Request &, Response &);
        void System(const Request &, Response &);
        void test();
    };
}
}
