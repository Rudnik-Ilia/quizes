#pragma once

#include <iostream>
using std::cout;
using std::endl;

#include <cstddef> // for size_t
#include <algorithm> // for stl algorithms
#include <bitset> 
#include <string.h>

static const unsigned char LUT[] = { 0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,
                                    4,5,5,6,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,
                                    5,5,6,5,6,6,7,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,
                                    5,6,4,5,5,6,5,6,6,7,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,4,5,5,6,
                                    5,6,6,7,5,6,6,7,6,7,7,8 
                                    };

class BiAddition
{
    public:
        BiAddition(size_t* other_arr) : array(other_arr){};
        size_t operator()(size_t x)
        {
           return x |= *array++;
        }
    private:
        size_t* array;
};

class BiMulti
{
    public:
        BiMulti(size_t* other_arr) : array(other_arr){};
        size_t operator()(size_t x)
        {
           return x &= *array++;
        }
    private:
        size_t* array;
};

class BiBird
{
    public:
        BiBird(size_t* other_arr) : array(other_arr){};
        size_t operator()(size_t x)
        {
           return x ^= *array++;
        }
    private:
        size_t* array;
};

class Count
{
    public:
        BiBird(size_t* other_arr) : array(other_arr){};
        size_t operator()(size_t x)
        {
           return x ^= *array++;
        }
    private:
        size_t* array;
};