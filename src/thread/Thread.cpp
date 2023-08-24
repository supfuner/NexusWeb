#include <cstring> // for strerror()
#include <cerrno> // for errno
#include "Thread.h"
using namespace pisco::thread;

bool pisco::thread::_SetThreadName(pthread_t thread_handle, const std::string& name) 
{
    int ret = -1;
#ifdef __linux__
        ret = pthread_setname_np(thread_handle, name.c_str());
        if (ret != 0)
        {
            std::cerr << "Failed to set thread name: " << strerror(errno) << std::endl;
        }
        
#else
    #warning "set_thread_name() is not implemented on this platform."
#endif
    return ret;
}

std::string pisco::thread::_GetThreadName(pthread_t thread_handle)
{
    char name[16];
#ifdef __linux__
    pthread_getname_np(thread_handle, name, 16);
#else
    #warning "get_thread_name() is not implemented on this platform."
#endif
    return name;
}


bool Thread::set_thread_Name(const std::string &name)
{
    return _SetThreadName(m_thread.native_handle(), name);
}

std::string Thread::get_thread_name() {
    // try
    // {
    //     return _GetThreadName(m_thread.native_handle());
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
       
    // }
    return m_name;
    
}