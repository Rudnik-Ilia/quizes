#include <sys/inotify.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <dlfcn.h> // dlopen
#include <iostream>
#include <boost/algorithm/string/predicate.hpp>

#include "DirMonitor.hpp"

#define BUFF_SIZE (4096)

namespace ilrd
{
    DirMonitor::DirMonitor(std::string dirpath): m_path(dirpath), m_thread(std::bind(&DirMonitor::Start, this)), m_inotify_fd(), m_stop(true){}

    DirMonitor::~DirMonitor()
    {
        m_stop = false;
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

    void DirMonitor::Start()
    {
        m_inotify_fd = inotify_init();
        if(m_inotify_fd < 0)
        {
            std::cout<< "ERROR inotify init" << std::endl;
            throw std::runtime_error("ERROR inotify init"); 
        }

        int watch_desc = inotify_add_watch(m_inotify_fd, m_path.c_str(), IN_CREATE);

        if(watch_desc < 0)
        {
            close(m_inotify_fd);
            std::cout<< "ERROR inotify_add_watch" << std::endl;
            throw std::runtime_error("ERROR inotify_add_watch");
        }

        int flags = fcntl(m_inotify_fd, F_GETFL, 0);
        fcntl(m_inotify_fd, F_SETFL, flags | O_NONBLOCK);

        fd_set set = {0};
        struct timeval tv;
       
        while(m_stop)
        {
            // fd_set set_copy = set;

            FD_ZERO(&set);  
            FD_SET(m_inotify_fd, &set);

            tv.tv_sec = 3;
            tv.tv_usec = 0;
            
            int retval = select(FD_SETSIZE, &set, NULL, NULL, &tv);

            if(retval == -1 && errno != EAGAIN)
            {
                std::cout<< "ERROR select (-1)" << std::endl;
                throw std::runtime_error("ERROR select (-1)");
            }
            else if(retval)
            {
                std::cout<< "DATA IS READY!" << std::endl;
                ReadEvents(m_inotify_fd);
            }
            else
            {
                std::cout<< "Wait for data..." << std::endl;
            }
        }
    }

    void DirMonitor::ReadEvents(int m_fd)
    {   
        std::cout<< "read events" << std::endl;
        const struct inotify_event *event;
        char buffer[BUFF_SIZE] = {0};
        char *ptr;

        while (m_stop)
        {
            int len = read(m_fd, buffer, BUFF_SIZE);

            if (len == -1 && errno != EAGAIN) 
            {
               std::cout<< "ERROR len" << std::endl;
            }
            if (len <= 0)
            {
                break;
            }
            for(ptr = buffer; ptr < buffer + len; ptr += sizeof(event) + event->len)
            {
                event = (const struct inotify_event *)ptr;

                std::string suffix = ".so";

                if (boost::algorithm::ends_with(std::string(event->name), suffix))
                {
                    m_dispatcher.Dispatch(std::string(m_path + '/' + event->name));
                }
            }
        }  
    }
/******************************************************************************************************/

    DllLoader::DllLoader(DirMonitor &monitor_) : m_subscriber([&](const std::string &filepath_){HandleCall(filepath_);}), m_monitor(monitor_)
    {
        m_monitor.AddLoader(m_subscriber);
    }

    void DllLoader::HandleCall(const std::string &filepath_)
    {
        #ifdef NDEBUG
        std::cout << filepath_.c_str() << std::endl;
        #endif 

        void *dl_handler = dlopen(filepath_.c_str(), RTLD_LAZY);

        if(NULL == dl_handler)
        {
            throw std::runtime_error("dlopen mistake");
        }
        m_container.push_back(dl_handler);
    }

    DllLoader::~DllLoader()
    {
        m_monitor.RemoveLoader(m_subscriber);
        for(auto iter: m_container)
        {
            dlclose(iter);
        }
    }

}