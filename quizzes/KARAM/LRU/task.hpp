#pragma once

#include <iostream>
#include <list>
#include <array>

template<size_t size>
class Summarray
{
    public:
        Summarray(): curr_sum(0)
        {
            most_sum = ((1 + size)*size)/2; 
            std::fill(std::begin(m_array), std::end(m_array), m_list.end());
        }

        void Insert(int num)
        {
            if(!Check(num))
            {
                m_list.push_back(num);
                auto iter = m_list.end();
                --iter;
                m_array[num] = iter;
                curr_sum += num;
            }
        }

        void Delete(int num)
        {
            auto iter = m_array[num];
            m_list.erase(iter);
            m_array[num] = m_list.end();
            curr_sum -= num;
        }

        size_t Summ()
        {
            return curr_sum;
        }

        bool Check(int num)
        {
            return m_array[num] != m_list.end();
        }

        bool IsEmpy()
        {
            return !curr_sum;
        }

        bool IsFull()
        {
            return curr_sum == most_sum;
        }

        int First()
        {
            auto iter = m_list.begin();
            return *(iter);
        }
        int Previous(int num)
        {
            auto iter = m_array[num];
            return *(--iter);
        }

    private:
        size_t most_sum;
        size_t curr_sum;
        std::list<int> m_list;
        std::array<std::list<int>::iterator, size + 1> m_array;
};