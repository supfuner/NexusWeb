#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "../web/Request.h"
#include "../web/Response.h"
using namespace pisco::web;

#include "ClassRegister.h"
#include "Register.h"

#include "../utility/Render.h"



namespace pisco{
namespace control{

class ClassFactory;

class BaseControl
{
public:
    BaseControl();
    virtual ~BaseControl();
    void setClassName(string name);
    template<typename R = void, typename ...Args>
    R exec(const string method, Args&... args);
private:
    string m_class_name;
};

template<typename R = void, typename ...Args>
R BaseControl::exec(const string method, Args&... args)
{

    uintptr_t func = Singleton<ClassFactory>::instance()->GetMethod(m_class_name, method);
    if(0 != func){
        std::function<R(decltype(this), Args&...)> * storeFunc = reinterpret_cast<std::function<R(decltype(this), Args&...)> *>(func);
        //std::cout<<"exec:"<<this<<"\tm_class_name:"<<m_class_name<<"\tmethod:"<<method<<"\n";
        return (*storeFunc)(this, args...); 
    }
    else{
        ostringstream os;
        os<<" exec method:"<<method<<"\tnot exists!\n";
        try
        {
            throw std::logic_error(os.str());
        }
        catch(const std::logic_error& e)
        {
            std::cerr << e.what();
        }        
    }

};



}
}
