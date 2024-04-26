#pragma once

#include <iostream>
#include <vector>

#include "ITask.hpp"
#include "Factory.hpp"
#include "Transmitter.hpp"


namespace ilrd
{
    struct ArgumentsForTask : public FactoryArgs
    {
        ArgumentsForTask(std::shared_ptr<std::vector<char>> data, 
                        u_int64_t handle,
                        u_int64_t from, 
                        u_int32_t len, 
                        uint32_t type, 
                        void *utils )
        : m_data(data), m_handle(handle), m_from(from), m_len(len), m_type(type), m_utils(utils)
        {}

        std::shared_ptr<std::vector<char>> m_data;
        u_int64_t m_handle;
        u_int64_t m_from;
        u_int32_t m_len;
        uint32_t m_type;
        void *m_utils;
    };

    /*****READING***************************************************************************************************/

    class ReadFunc: public ITask
    {
        public:
            ReadFunc(u_int64_t handle, u_int64_t from, u_int32_t len, uint32_t type, void *utils): m_handle(handle), m_from(from), m_len(len), m_type(type), m_utils(utils){}
            void Execute()
            {   
                std::cout << "HI FROM READ TASK!" << '\n';
                std::cout << "OFFSET: " << m_from << '\n';
                std::cout << "SIZEOF VECTOR: " << m_len << '\n'; 
                
                reinterpret_cast<Transmitter*>(m_utils)->SendRead(m_len, m_from, m_type, m_handle);
            }
            
        private:
            u_int64_t m_handle;
            u_int64_t m_from;
            u_int32_t m_len;
            uint32_t m_type;
            void * m_utils;
    };

    
    /*****WRITING***************************************************************************************************/


    class WriteFunc: public ITask
    {
        public:
            WriteFunc(std::shared_ptr<std::vector<char>> data, u_int64_t handle, u_int64_t from, u_int32_t len, uint32_t type, void *utils): m_data(data), m_handle(handle), m_from(from), m_len(len), m_type(type), m_utils(utils){}
            void Execute()
            {
                std::cout << "HI FROM WRITE TASK!" << '\n';
                std::cout << "OFFSET: " << m_from << '\n';
                std::cout << "LEN: " << m_len << '\n';
                std::cout << "SIZEOF VECTOR: " << m_data.get()->size() << '\n'; 
                
                reinterpret_cast<Transmitter*>(m_utils)->SendWrite(m_data, m_from, m_type);
            }

        private:
            std::shared_ptr<std::vector<char>> m_data;
            u_int64_t m_handle;
            u_int64_t m_from;
            u_int32_t m_len;
            uint32_t m_type;
            void *m_utils; 
    };

    /**********************************************************************************************************/

    class Creator
    {
        public:

            static std::shared_ptr<ITask> Get_Read_Task(FactoryArgs& Args)
            {
                ArgumentsForTask &args =  dynamic_cast<ArgumentsForTask&>(Args);
                return std::shared_ptr<ReadFunc>(new ReadFunc(args.m_handle, args.m_from, args.m_len, args.m_type, args.m_utils));
            }

            static std::shared_ptr<ITask> Get_Write_Task(FactoryArgs& Args)
            {
                ArgumentsForTask &args =  dynamic_cast<ArgumentsForTask&>(Args);
                return std::shared_ptr<WriteFunc>(new WriteFunc(args.m_data, args.m_handle, args.m_from, args.m_len, args.m_type, args.m_utils));
            }

        private:
            Creator();
    };
}
