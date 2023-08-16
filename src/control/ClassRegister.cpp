#include "ClassRegister.h"
using namespace pisco::control;


ClassRegister::ClassRegister(const string & className, ObjCreater method)
{
    Singleton<ClassFactory>::instance()->RegisterClass(className, method);
}

ClassRegister::ClassRegister(const string & className, const string & methodName, uintptr_t method)
{
    Singleton<ClassFactory>::instance()->RegisterMethod(className, methodName, method);
}