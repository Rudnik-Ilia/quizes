#ifndef __ILRD_RD132_DIRMONITOR_HPP__
#define __ILRD_RD132_DIRMONITOR_HPP__

#include <string> // std::string
#include <thread> // std:: thread
#include <list>

#include "Dispatcher.hpp"

namespace ilrd
{
    class DirMonitor
    {
    public:
        explicit DirMonitor(std::string dirpath);

        // DirMonitor moveable but not copyable
        DirMonitor(DirMonitor &&) = default;
        DirMonitor(const DirMonitor &) = delete;
        DirMonitor &operator=(DirMonitor &&) = default;
        DirMonitor &operator=(const DirMonitor &) = delete;

        void AddLoader(const Callback<std::string> &dll_loader_);
        void RemoveLoader(const Callback<std::string> &dll_loader_);
        ~DirMonitor();

        void Monitor();
    private:
        Dispatcher<std::string> m_dispatcher;

        std::string m_path;
        std::thread m_thread;

        void Start();
        void ReadEvents(int m_fd);

        int m_inotify_fd;
        int m_stop;
    }; 

/*******************************************************************************/

    class DllLoader
    {
    public:
        explicit DllLoader(DirMonitor &monitor_);
    
        DllLoader(DllLoader &&) = default;
        DllLoader(const DllLoader &) = default;
        DllLoader &operator=(DllLoader &&) = default;
        DllLoader &operator=(const DllLoader &) = default;

        ~DllLoader();

    private:
        Callback<std::string> m_subscriber;
        DirMonitor &m_monitor;
        std::list<void*> m_container;
    }; 

} // namespace ilrd

#endif // __ILRD_RD132_DIRMONITOR_HPP__