#pragma once


namespace pisco{
namespace utility{
    
template <typename T>
class Singleton
{
public:
    ~Singleton() {};
    Singleton<T> & operator = (const Singleton<T> &) = delete;
    static T & instance()
    {
        static T m_instance;
        // if (m_instance == NULL)
        //     m_instance = new T();
        return m_instance;
    }

private:
    Singleton() {}
    Singleton(const Singleton<T> &);

private:
    static T * m_instance;
};

template <typename T>
T * Singleton<T>::m_instance = NULL;
}
}