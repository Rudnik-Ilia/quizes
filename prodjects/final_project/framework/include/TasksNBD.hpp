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
        ArgumentsForTask(std::shared_ptr<std::vector<char>> data, u_int64_t from, u_int32_t len, uint32_t type): m_data(data), m_from(from), m_len(len), m_type(type){}
        std::shared_ptr<std::vector<char>> m_data;
        u_int64_t m_from;
        u_int32_t m_len;
        uint32_t m_type;
    };

    /*****READING***************************************************************************************************/

    class ReadFunc: public ITask
    {
        public:
            ReadFunc(std::shared_ptr<std::vector<char>> data, u_int64_t from, u_int32_t len, uint32_t type): m_data(data), m_from(from), m_len(len), m_type(type), m_transmitter(){}
            void Execute()
            {   
                std::cout << "HI FROM READ TASK!" << '\n';
                std::cout << "OFFSET: " << m_from << '\n';
                std::cout << "SIZEOF VECTOR: " << m_data.get()->size() << '\n'; 
                
                // m_transmitter.Send(m_data, m_from, m_type);
            }
            
        private:
            std::shared_ptr<std::vector<char>> m_data;
            u_int64_t m_from;
            u_int32_t m_len;
            uint32_t m_type;
            Transmitter m_transmitter;
    };

    /*****WRITING***************************************************************************************************/


    class WriteFunc: public ITask
    {
        public:
            WriteFunc(std::shared_ptr<std::vector<char>> data, u_int64_t from, u_int32_t len, uint32_t type): m_data(data), m_from(from), m_len(len), m_type(type), m_transmitter(){}
            void Execute()
            {
                std::cout << "HI FROM WRITE TASK!" << '\n';
                std::cout << "OFFSET: " << m_from << '\n';
                std::cout << "LEN: " << m_len << '\n';
                std::cout << "SIZEOF VECTOR: " << m_data.get()->size() << '\n'; 
                
                m_transmitter.Send(m_data, m_from, m_type);
            }

        private:
            std::shared_ptr<std::vector<char>> m_data;
            u_int64_t m_from;
            u_int32_t m_len;
            uint32_t m_type;
            Transmitter m_transmitter;
            
    };

    /**********************************************************************************************************/

    class Creator
    {
        public:

            static std::shared_ptr<ITask> Get_Read_Task(FactoryArgs& Args)
            {
                ArgumentsForTask &args =  dynamic_cast<ArgumentsForTask&>(Args);
                return std::shared_ptr<ReadFunc>(new ReadFunc(args.m_data, args.m_from, args.m_len, args.m_type));
            }

            static std::shared_ptr<ITask> Get_Write_Task(FactoryArgs& Args)
            {
                ArgumentsForTask &args =  dynamic_cast<ArgumentsForTask&>(Args);
                return std::shared_ptr<WriteFunc>(new WriteFunc(args.m_data, args.m_from, args.m_len, args.m_type));
            }

        private:
            Creator();
    };
}
