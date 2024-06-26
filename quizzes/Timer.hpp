#pragma once

#include <chrono>
#include <iostream>


class MyTimer
{
    using my_clock = std::chrono::high_resolution_clock;
    using McS = std::chrono::microseconds;
    using MLcS = std::chrono::milliseconds;

    public:
        MyTimer(): m_start(my_clock::now()){}
        ~MyTimer()
        {
            std::cout << "TIME IS: " << (std::chrono::duration_cast<MLcS>(my_clock::now() - m_start).count()) << " millisecond" <<  std::endl;
        }

    private:
        my_clock::time_point m_start;

};