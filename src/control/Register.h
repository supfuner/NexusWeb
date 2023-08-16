#include "BaseControl.h"
#include "ClassRegister.h"



#define REGISTER_CLASS(className)                                       \
    shared_ptr<BaseControl> createControl##className()                  \
    {                                                                   \
        shared_ptr<BaseControl> ctl = std::make_shared<className>();    \
        ctl->setClassName(#className);                                  \
        return ctl;                                                     \
    }                                                                  	\
    ClassRegister classRegister##className(#className, createControl##className)

#define REGISTER_CLASS_METHOD(className, methodName,returnType, ...) \
    std::function<returnType(className *, ##__VA_ARGS__)> className##methodName##method = &className::methodName; \
    ClassRegister classRegister##className##methodName(#className, #methodName, (uintptr_t)&(className##methodName##method))

