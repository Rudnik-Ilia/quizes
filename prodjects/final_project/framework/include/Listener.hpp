#ifndef __ILRD_RD132_LISTENER_HPP__
#define __ILRD_RD132_LISTENER_HPP__

#include "Reactor.hpp"

namespace ilrd
{

    class Listener: IFDListener
    {
        Listener() = default;
        Listener(Listener &&) = default;
        Listener(const Listener &) = default;
        Listener &operator=(Listener &&) = default;
        Listener &operator=(const Listener &) = default;

        virtual ~Listener() = default;

        std::list<Reactor::EventKey> Listen(const Reactor::ConnectionMap &);
    };

}



#endif /* __ILRD_RD132_LISTENER_HPP__ */