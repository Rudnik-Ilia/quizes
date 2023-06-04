#pragma once

#include <linux/nbd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <vector>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#include "Receiver.hpp"
#include "ThreadPool.hpp"
#include "Factory.hpp"
#include "Reactor.hpp"
#include "Listener.hpp"

using namespace std;


namespace ilrd
{   
    class Minion
    {
        public:
            Minion(uint16_t port);
            ~Minion();

            void Wait();


        private:

            Receiver m_receiver;
            // Factory<ITask, Reactor::ioMode> m_factory;
            // ThreadPool m_pool;
            // Reactor m_reactor;
            // Transmitter m_transmitter;
    };

    Minion::Minion(uint16_t port): m_receiver(port)
    {
        
    }

    Minion::~Minion()
    {

    }

    void Minion::Wait()
    {
        m_receiver.Listen();
    }

}