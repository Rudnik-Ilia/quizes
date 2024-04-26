#include <iostream>

#include "../include/Connector.hpp"
#include "../include/PoolConn.hpp"

using namespace ilia;

int main()
{
    PoolConn("dbname = ilia user = ilia password = 12345 hostaddr = 172.19.0.3 port = 5432", 12);


    sleep(30);


    return 0;
}