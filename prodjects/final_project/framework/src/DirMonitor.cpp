#include <sys/inotify.h>


#include "DirMonitor.hpp"


namespace ilrd
{

    DirMonitor::DirMonitor(std::string dirpath): m_path(dirpath), m_thread()
    {
        int inotify_fd = inotify_init();
        int watch_desc = inotify_add_watch(inotify_fd, m_path.c_str(), IN_MODIFY);
    }

    DirMonitor::~DirMonitor()
    {
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
        
    }

    /*******************************************************************************/


    DllLoader::DllLoader(DirMonitor &monitor_): m_monitor(monitor_)
    {

    }
  

    DllLoader::~DllLoader()
    {

    }

}