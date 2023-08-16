#include "ClassFactory.h"
using namespace pisco::control;


void ClassFactory::RegisterClass(const string className, ObjCreater obj)
{
    m_class_map.insert(pair<string, ObjCreater>(className, obj));
}

void ClassFactory::RegisterMethod(const string className, const string methodName, uintptr_t method)
{
    auto it = m_method_map.find(className);
    if (it != m_method_map.end())
    {
        it->second.insert(pair<std::string, uintptr_t>(methodName, method));
    }
    else{
        std::map<std::string, uintptr_t> methodInnerMap;
        methodInnerMap[methodName] = method;
        m_method_map[className] = methodInnerMap;
    }   
}


shared_ptr<BaseControl> ClassFactory::CreateControl(const string className)
{
    auto it = m_class_map.find(className);
    if (it != m_class_map.end())
    {
        //std::cout<<"Register insert "<<className<<":"<< it->second() << "\n";
        return it->second();
    }
    return nullptr;
}

uintptr_t ClassFactory::GetMethod(const string className, const string methodName)
{
    auto it = m_method_map.find(className);
    if (it != m_method_map.end())
    {
        auto mtd = it->second.find(methodName);
        if (mtd != it->second.end())
        {
            return mtd->second;
        }        
    }
    return 0;
}



