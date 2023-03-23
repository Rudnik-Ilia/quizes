
#include "Listener.hpp"
#include "Reactor.hpp"


namespace ilrd
{

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
        while(!m_stop_flag)
        {   
            auto readyness = m_listener->Listen(m_connections);
            for(auto iter: readyness)
            {
                iter.second;
            }
        }
    }

    void Reactor::Stop()
    {
        m_stop_flag = true;
    }

}