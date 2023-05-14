#pragma once

#include <iostream>
#include "Singleton.hpp"
#include "NBD.hpp"
#include "Reactor.hpp"
#include "Listener.hpp"
#include "Factory.hpp"
#include "ITask.hpp"
#include "TasksNBD.hpp"
#include "ThreadPool.hpp"

namespace ilrd
{
    class FRAME
    {
        void Show(void *dat, u_int64_t offset, u_int32_t len)
        {
            for (size_t i = 0; i < len; i++)
            {
                std::cout<<  *((char*)dat + offset + i);
            }  
        }
        public:
            FRAME(NBDServer& nbd): m_nbd(nbd) , m_reactor(std::move(std::unique_ptr<Listener>(new Listener()))), m_pool(3), m_factory()
            {
                m_nbd.Start();
                m_reactor.Register({STDIN_FILENO, Reactor::ioMode::READ}, std::bind(&FRAME::StopFunc, this));
                m_reactor.Register({m_nbd.GetDescriptor(), Reactor::ioMode::READ}, std::bind(&FRAME::Run_NBD, this));
            };

            ~FRAME(){};

            void Run_NBD()
            {
                m_nbd.Serve();
                
                if(m_nbd.GetArguments().get()->m_type == NBD_CMD_READ)
                {
                    std::cout << "READING" << std::endl;
                    std::cout <<  m_nbd.GetArguments().get()->m_from << std::endl;
                    std::cout << m_nbd.GetArguments().get()->m_len << std::endl;
                    std::cout << m_nbd.GetArguments().get()->m_type << std::endl;
                    auto task = m_factory.Create(Reactor::ioMode::READ, *(m_nbd.GetArguments().get()));
                    m_pool.AddTask(task, ThreadPool::PRIORITY_HIGH);
                    return;
                }
                if(m_nbd.GetArguments().get()->m_type == NBD_CMD_WRITE)
                {
                    std::cout << "WRITING" << std::endl;
                    std::cout <<  m_nbd.GetArguments().get()->m_from << std::endl;
                    std::cout << m_nbd.GetArguments().get()->m_len << std::endl;
                    std::cout << m_nbd.GetArguments().get()->m_type << std::endl;
                    auto task = m_factory.Create(Reactor::ioMode::WRITE, *(m_nbd.GetArguments().get()));
                    m_pool.AddTask(task, ThreadPool::PRIORITY_HIGH);
                    return;
                }

            }

            void Run_Reactor()
            {
                m_reactor.Run();
            }

            void Register(const Reactor::ioMode& key, std::function<std::shared_ptr<ITask> (FactoryArgs&)> creator)
            {
                m_factory.Register(key, creator);
            }
  
        private:
            void StopFunc()
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
    };
}