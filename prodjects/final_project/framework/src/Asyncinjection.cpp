#include "Asyncinjection.hpp"


namespace ilrd
{
    Scheduler* AsyncInjection::m_sched = Singleton<Scheduler>::GetInstance();

    AsyncInjection::AsyncInjection(const std::function<bool()> &action_, std::chrono::milliseconds timeout_): m_shared_task(std::shared_ptr<AsyncTask>(new AsyncTask(action_, this))), m_interval(timeout_)
    {
        m_sched->AddTask(std::shared_ptr<AsyncTask>(m_shared_task), m_interval);
    }
    AsyncInjection::~AsyncInjection()
    {

    }

    /*********************************************************************************/

    AsyncInjection::AsyncTask::AsyncTask(const std::function<bool()> &action_, AsyncInjection* injector_): m_action(action_), my_injector(injector_){}

    void AsyncInjection::AsyncTask::Execute()
    {
        if(!m_action())
        {
            my_injector->m_sched->AddTask(my_injector->m_shared_task, my_injector->m_interval);
        }
        else
        {
            #ifdef NDEBUG
            std::cout << "STOP" << std::endl;
            #endif
            delete my_injector;
        }
    }
}