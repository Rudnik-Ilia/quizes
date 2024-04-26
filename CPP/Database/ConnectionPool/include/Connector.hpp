#pragma once

#include <iostream>
#include <memory>
#include <pqxx/pqxx>
#include<unistd.h> 

namespace ilia
{
    class Connector
    {    
        public:
            Connector(const std::string user_pass_db);
            ~Connector();

            std::shared_ptr<pqxx::connection> GetConn() const;
            std::string GetNameDB() const;

        private:
            std::shared_ptr<pqxx::connection> m_conn;
            std::string m_dbname;
    };
    
    Connector::Connector(const std::string user_pass_db) try : m_conn(std::make_shared<pqxx::connection>(user_pass_db))
    {
        if(m_conn.get()->is_open())
        {
            m_dbname = m_conn.get()->dbname();
        } 
        else 
        {
            std::cout << "Can't open database" << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    std::shared_ptr<pqxx::connection> Connector::GetConn() const
    {
        return m_conn;
    } 

    std::string Connector::GetNameDB() const
    {
        return m_dbname;
    }

    Connector::~Connector()
    {
        m_conn.get()->disconnect();
    }
    
}