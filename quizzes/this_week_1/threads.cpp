#include <iostream>
#include <thread>
#include <unistd.h>
#include <future>
#include <pthread.h>
#include <iostream>
// #include <boost/asio.hpp>
// #include <boost/beast.hpp>
// #include <boost/beast/http.hpp>


// static size_t counter = 0;
static volatile size_t counter = 0;


void * Work(void *args)
{
    for(int i = 0; i < 1000000; ++i)
    {
        // std::lock_guard<std::mutex> lock(counterMutex);
        counter++;
    }
    return nullptr;
}

int main() 
{
    pthread_t thread1;
    pthread_t thread2;

    pthread_attr_t attr1;
    pthread_attr_t attr2;

    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    int priority1 = -19;
    int priority2 = 19;

    sched_param param1;
    sched_param param2;

    param1.sched_priority = priority1;
    param1.sched_priority = priority2;

    pthread_attr_setschedparam(&attr1, &param1);
    pthread_attr_setschedparam(&attr2, &param2);

    pthread_create(&thread1, &attr1, Work, nullptr);
    pthread_create(&thread2, &attr2, Work, nullptr);

    pthread_attr_destroy(&attr1);
    pthread_attr_destroy(&attr2);

    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    std::cout << counter << std::endl;

    return 0;
}

