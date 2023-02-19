#include <iostream>
#include <pthread.h>

#include "scope.hpp"

using namespace ilrd;


int main()
{
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    {
        ScopeLock <pthread_mutex_t>Scopelock(&lock);
        pthread_mutex_lock(&lock);
    }

    std::cout << "trylock: " << pthread_mutex_trylock(&lock) << std::endl;
    pthread_mutex_lock(&lock);

    return 0;
}