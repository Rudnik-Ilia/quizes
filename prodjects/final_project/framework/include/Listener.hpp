#pragma once

#include "Reactor.hpp"

namespace ilrd
{
    class Listener: public IFDListener
    {
        public:

            std::list<Reactor::EventKey> Listen(const Reactor::ConnectionMap &map_key_connection) 
            {
                for(auto iter: map_key_connection)
                {
                    iter.first.first;
                }
            }
        private:

    };

}
