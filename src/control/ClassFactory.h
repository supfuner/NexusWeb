#pragma once

#include <functional>
#include <memory>
#include <map>
#include <vector>
using namespace std;
#include "BaseControl.h"
#include "../utility/Singleton.h"
using namespace pisco::utility;


namespace pisco{
namespace control{
    class BaseControl;
    using ObjCreater = function<shared_ptr<BaseControl>()>;
    class ClassFactory
    {
        friend class Singleton<ClassFactory>;
    public:
        void RegisterClass(const string className, ObjCreater obj);
        void RegisterMethod(const string className, const string methodName, uintptr_t method);
        uintptr_t GetMethod(const string className, const string methodName);
        shared_ptr<BaseControl> CreateControl(const string className);
    private:
        ClassFactory(){};
        virtual ~ClassFactory(){};

    private:
        map<string, ObjCreater> m_class_map;
        map<string, map<string, uintptr_t>> m_method_map;
    };
}
}