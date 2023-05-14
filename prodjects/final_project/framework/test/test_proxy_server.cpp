#include <vector>
#include "ProxyServer.hpp"

using namespace ilrd;


int main()
{

    Proxy_Server serv(8888);
    int fd = serv.Get_FD();

    serv.Write_Smt("Hi from nowhere!", 4096, 8888);

    char buffer[1024] = {0};
    struct sockaddr_in client_addr; 
    socklen_t len = 0; 
    memset(&client_addr, 0, LENGHT);

    recvfrom(fd, (char *)buffer, 1024, 0, (struct sockaddr*)&client_addr, &len); 

    std::cout << "From server :" << buffer << std::endl; 

    return 0;
}
