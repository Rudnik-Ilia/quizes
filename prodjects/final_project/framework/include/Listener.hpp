#pragma once

#include <iostream>
#include <sys/select.h> 
#include <sys/time.h>   
#include <sys/types.h>  
#include <unistd.h>     

#include "Reactor.hpp"

namespace ilrd
{
    class Listener: public IFDListener
    {
        public:
            std::list<Reactor::EventKey> Listen(const Reactor::ConnectionMap &map_key_connection) 
            {
                std::list<Reactor::EventKey> Ready_fd;
                 
                fd_set Read_fd = {0};
                fd_set Write_fd = {0};

                FD_ZERO(&Read_fd);
                FD_ZERO(&Write_fd);

                for(auto iter: map_key_connection)
                {
                    switch (iter.first.second)
                    {
                        case Reactor::ioMode::READ:

                            FD_SET(iter.first.first, &Read_fd);
                            break;

                        case Reactor::ioMode::WRITE:

                            FD_SET(iter.first.first, &Write_fd);
                            break;
                        
                        default:
                            break;
                    }

                    struct timeval tv;
                    tv.tv_sec = 0;
                    tv.tv_usec = 10;

                    int retval = select(FD_SETSIZE, &Read_fd, &Write_fd, NULL, &tv);

                    if(retval == -1)
                    {
                        std::cout<< "ERROR select (-1)" << std::endl;
                    
                    }
                    else if(retval == 0)
                    {
                        // std::cout<< "Wait for data..." << std::endl;
                    }

                    for(size_t i = 0; i < FD_SETSIZE; ++i)
                    {
                        if(FD_ISSET(i, &Read_fd))
                        {
                            Reactor::EventKey fd_mode_key(i, Reactor::ioMode::READ);
                            Ready_fd.push_back(fd_mode_key);
                        }
                        if(FD_ISSET(i, &Write_fd))
                        {
                            Reactor::EventKey fd_mode_key(i, Reactor::ioMode::WRITE);
                            Ready_fd.push_back(fd_mode_key);
                        }
                    }      
                }
                
                return Ready_fd;
            }
    };

}
