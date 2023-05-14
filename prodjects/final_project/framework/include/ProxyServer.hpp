#pragma once

#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <string.h> 
#include <sys/types.h>              
#include <stdio.h>    
#include <errno.h>                         
  
#define LENGHT sizeof(struct sockaddr_in)
#define BACKLOG (3)

namespace ilrd
{
    class Proxy_Server
    {
        public:
            explicit Proxy_Server(int port)
            {
                struct sockaddr_in server_addr;
                memset(&server_addr, 0, LENGHT);

                if (0 > (m_fd = socket(AF_INET, SOCK_DGRAM, 0)))
                {
                    fprintf(stderr, "Socket from Ctor failed. errno: %d\n", errno);
                }
                server_addr.sin_family = AF_INET; 
                server_addr.sin_port = htons(port);
                server_addr.sin_addr.s_addr = INADDR_ANY; 

                if( 0 > (bind(m_fd, (struct sockaddr *)&server_addr, LENGHT)))
                {
                    fprintf(stderr, "Bind from Ctor failed. errno: %d\n", errno);
                }
            }
            ~Proxy_Server()
            {
                close(m_fd);
            }

            int Write_Smt(char *data, size_t data_size, int port)
            {
                struct sockaddr_in client_addr;
                memset(&client_addr, 0, LENGHT);

                client_addr.sin_family = AF_INET; 
                client_addr.sin_port = htons(port); 
                client_addr.sin_addr.s_addr = INADDR_ANY; 

                int nbytes = sendto(m_fd, data, data_size, MSG_CONFIRM, (const struct sockaddr*)&client_addr, LENGHT);

                if(nbytes < 0)
                {
                    fprintf(stderr, "Bind from Ctor failed. errno: %d\n", errno);
                    return 1;
                }
                return 0;
            }

            int Read_Smt()
            {
                return 0;
            }
            
            int Get_FD()
            {
                return m_fd;
            }

        private:
            int m_fd;
    };
}