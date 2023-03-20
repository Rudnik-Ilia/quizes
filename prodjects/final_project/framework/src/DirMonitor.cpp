#include <DirMonitor.hpp>


namespace ilrd
{

    DirMonitor::DirMonitor(std::string dirpath): m_path(dirpath), m_thread()
    {

    }

    DirMonitor::~DirMonitor()
    {

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

    }

    /*******************************************************************************/


    DllLoader::DllLoader(DirMonitor &monitor_): m_monitor(monitor_)
    {
        
    }
  

    DllLoader::~DllLoader()
    {

    }

}