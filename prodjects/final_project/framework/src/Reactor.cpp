#include <iostream>
#include "Listener.hpp"
#include "Reactor.hpp"


namespace ilrd
{
    
    // class Functor
    // {
    //     public:
    //         void operator()(std::list<Reactor::EventKey> readyFD){

    //         }


    // };

    Reactor::Reactor(ListenerPtr listener_) : m_listener(std::move(listener_)){}

    Reactor::~Reactor()
    {   
        m_connections.clear();
    }

    void Reactor::Register(const EventKey &key_, EventCallback handler_)
    {
        m_connections.insert({key_, handler_});
    }

    void Reactor::Unregister(const EventKey &key_)
    {
        m_connections.erase(key_);
    }

    void Reactor::Run()
    {
        while(!m_stop_flag && !m_connections.empty())
        {   
            std::list<Reactor::EventKey> readyFD = m_listener->Listen(m_connections);
            
            for(auto iter: readyFD)
            {   
                if(m_stop_flag)
                {
                    break;
                }
                m_connections.at(iter)();   
            }
        }
    }

    void Reactor::Stop()
    {
        m_stop_flag = true;
    }

}