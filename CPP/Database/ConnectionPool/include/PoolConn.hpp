#pragma once

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "Connector.hpp"

namespace ilia
{
    class PoolConn
    {
        public:
            PoolConn(const std::string user_pass_db, size_t size);
            ~PoolConn();

            std::shared_ptr<pqxx::connection> GetDB();

            void BackDB(std::shared_ptr<pqxx::connection>& conn);

        private:
            size_t len_of_pool;

            std::mutex m_mutex{};
            std::condition_variable m_cond{};

            std::queue<std::shared_ptr<pqxx::connection>> m_pool;  
    };

    PoolConn::PoolConn(const std::string user_pass_db, size_t size): len_of_pool(size), m_pool()
    {
        for(size_t i = 0; i < len_of_pool; ++i)
        {
            auto item = new Connector(user_pass_db);
            m_pool.emplace(item->GetConn());
        }
    }

    PoolConn::~PoolConn()
    {
        for(size_t i = 0; i < len_of_pool; ++i)
        {
           
        }
    }

    std::shared_ptr<pqxx::connection> PoolConn::GetDB()
    {
        {
            std::unique_lock<std::mutex> lock(m_mutex); 
            while (m_pool.empty())
            {
                m_cond.wait(lock);
            }

            auto conn = m_pool.front();
            m_pool.pop();
            return conn;
        }
    }

    void PoolConn::BackDB(std::shared_ptr<pqxx::connection>& conn)
    {

    }


}