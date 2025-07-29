
#pragma once

namespace PatternTool{

template<class T>
class Singleton{
    public:
        static T* instance(){
            if(!m_inst){
                m_inst =  new T();
            }
            return m_inst;
        }

        static void destroy(){
            if(m_inst){
                delete m_inst;
                m_inst = nullptr;
            }
        }

    private:
        Singleton(){}
        Singleton(const Singleton &) = delete;
        Singleton & operator=(const Singleton & ) = delete;
        ~Singleton(){}
        static T* m_inst;
};

template<class T>
T* Singleton<T>::m_inst = nullptr;

}
