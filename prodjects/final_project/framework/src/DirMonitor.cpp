#include <sys/inotify.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <dlfcn.h> // dlopen
#include <iostream>

#include "DirMonitor.hpp"

#define BUFF_SIZE (1024)

namespace ilrd
{
    DirMonitor::DirMonitor(std::string dirpath): m_path(dirpath), m_thread(), m_inotify_fd(), m_stop(1)
    {
        m_inotify_fd = inotify_init();
        if(m_inotify_fd < 0)
        {
            std::cout<< "ERROR inotify init" << std::endl;
        }

        int watch_desc = inotify_add_watch(m_inotify_fd, m_path.c_str(), IN_ALL_EVENTS);

        if(watch_desc < 0)
        {
            std::cout<< "ERROR inotify_add_watch" << std::endl;
        }

        int flags = fcntl(m_inotify_fd, F_GETFL, 0);
        fcntl(m_inotify_fd, F_SETFL, flags | O_NONBLOCK);
    }

    DirMonitor::~DirMonitor()
    {
        m_thread.join();
        close(m_inotify_fd);
    }

    void DirMonitor::AddLoader(const Callback<std::string> &dll_loader_)
    {
        m_dispatcher.Subscribe(dll_loader_);
    }

    void DirMonitor::RemoveLoader(const Callback<std::string> &dll_loader_)
    {
        m_dispatcher.Unsubscribe(dll_loader_);
    }

    void DirMonitor::Monitor()
    {
        m_thread = std::thread(std::bind(&DirMonitor::Start, this));
    }

    void DirMonitor::Start()
    {
        fd_set set = {0};
        struct timeval tv;
       
        while(m_stop)
        {
            fd_set set_copy = set;

            FD_ZERO(&set);  
            FD_SET(m_inotify_fd, &set);

            tv.tv_sec = 3;
            tv.tv_usec = 0;
            
            int retval = select(FD_SETSIZE, &set_copy, NULL, NULL, &tv);

            if(retval == -1)
            {
                std::cout<< "ERROR select (-1)" << std::endl;
            }
            else if(retval)
            {
                std::cout<< "DATA IS READY!" << std::endl;
                ReadEvents(m_inotify_fd);
            }
            else
            {
                std::cout<< "No data within five seconds" << std::endl;
            }
        }
    }

    void DirMonitor::ReadEvents(int m_fd)
    {   
        std::cout<< "read events" << std::endl;
        char buffer[BUFF_SIZE];
        int length = read(m_inotify_fd, buffer, BUFF_SIZE);

    }

    DllLoader::DllLoader(DirMonitor &monitor_): m_subscriber([&](const std::string &filepath_)) , m_monitor(monitor_)
    {
        m_monitor.AddLoader(m_subscriber);
    }



    // DllLoader::~DllLoader()
    // {
    //     m_monitor.RemoveLoader(m_subscriber);
    // }

}