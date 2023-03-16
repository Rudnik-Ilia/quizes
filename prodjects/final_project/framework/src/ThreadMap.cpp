#include <unordered_map>
#include <mutex>
#include <thread> // std::thread::id
#include <memory> // shared_ptr

#include "WorkerThread.hpp"
#include "ThreadMap.hpp"

namespace ilrd
{
    void ThreadMap::Insert(const KeyValPair &kvPair_)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_threadMap.insert(kvPair_);
    }

    void ThreadMap::Remove(iterator pos_)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_threadMap.erase(pos_);
    }

    ThreadMap::iterator ThreadMap::Find(Key key_)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_threadMap.find(key_);
    }

    WorkerThread::State ThreadMap::GetState(Key key_) const
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        return  m_threadMap.find(key_)->second->GetState();
    }


}