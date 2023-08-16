#pragma once


#include <string>
using namespace std;

#include "../utility/Singleton.h"
using namespace pisco::utility;

#include "ClassFactory.h"
#include "BaseControl.h"


namespace pisco {
namespace control {
class BaseControl;
class ClassFactory;
using ObjCreater = function<shared_ptr<BaseControl>()>;
class ClassRegister
{
public:
    ClassRegister(const string & className, ObjCreater method);

    ClassRegister(const string & className, const string & methodName, uintptr_t method);
};



}
}
