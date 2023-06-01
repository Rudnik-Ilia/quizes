#pragma once

#include <iostream>
#include <errno.h>

#include "StaticListener.hpp"
#include "Singleton.hpp"
#include "NBD.hpp"
#include "Reactor.hpp"
#include "Listener.hpp"
#include "Factory.hpp"
#include "ITask.hpp"
// #include "TasksNBD.hpp"
#include "ThreadPool.hpp"


namespace ilrd
{
    class FRAME
    {
        public:

            explicit FRAME(NBDServer& nbd);
            ~FRAME();

            void Run_NBD();
            void Run_Reactor();
            void Register(const Reactor::ioMode& key, std::function<std::shared_ptr<ITask> (FactoryArgs&)> creator);
            void AddReadTask();
  
        private:
            inline void StopFunc()
            {
                char buffer[2] = {0};
                read(STDIN_FILENO, &buffer, 1);
                if(0 == strcmp(buffer, "x")) 
                {
                    m_reactor.Stop();
                }
            }

            NBDServer &m_nbd;
            Reactor m_reactor;
            ThreadPool m_pool;
            Factory<ITask, Reactor::ioMode> m_factory;
            Transmitter *m_transmit;
            StaticListener m_static_listen;
    };

}