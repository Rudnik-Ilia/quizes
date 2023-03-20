#include <sys/inotify.h>
#include <fstream>
#include <sys/select.h>
#include <fcntl.h>

#include "DirMonitor.hpp"

namespace ilrd
{
    DirMonitor::DirMonitor(std::string dirpath): m_path(dirpath), m_thread(), m_inotify_fd()
    {
        m_inotify_fd = inotify_init();
        int watch_desc = inotify_add_watch(m_inotify_fd, m_path.c_str(), IN_ALL_EVENTS);
    }

    DirMonitor::~DirMonitor()
    {
        // std::close(m_inotify_fd);
        m_thread.join();
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
        m_thread = std::thread(std::bind(DirMonitor::Start, this));
    }

    void DirMonitor::Start()
    {
        fd_set set = {0};
        struct timeval tv;

        FD_ZERO(&set);  
        FD_SET(m_inotify_fd, &set);
       

        while(true)
        {
            fd_set set_copy = set;
            tv.tv_sec = 7;
            tv.tv_usec = 0;
            int check = 0;

            check = select(FD_SETSIZE, &set_copy, NULL, NULL, &tv);

        }


    }

    /*******************************************************************************/


    DllLoader::DllLoader(DirMonitor &monitor_): m_monitor(monitor_)
    {

    }
  

    DllLoader::~DllLoader()
    {

    }

}