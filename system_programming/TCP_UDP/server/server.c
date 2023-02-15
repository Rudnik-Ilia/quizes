#include <stdio.h>          
#include <sys/types.h>      
#include <unistd.h>         
#include <arpa/inet.h>      
#include <stdlib.h>         
#include <string.h>         
#include <time.h>           
#include <sys/select.h>

#include "../header.h"

int main()
{
    int i = 0;

    struct sockaddr_in server_addr = {0};
    int tcp_server_fd = 0;
    int udp_server_fd = 0;

    int permission_tcp = 1;
    int permission_udp = 1;

    struct timeval tv;
    int retval = 0;
    fd_set set_desc = {0};
    fd_set set_desc_copy = {0};

    tv.tv_sec = 5;
    tv.tv_usec = 5;

    Fill_Struct(&server_addr);

    Make_Socket(&tcp_server_fd, 0);
    Make_Socket(&udp_server_fd, 1);

    CheckValue(bind(tcp_server_fd, (struct sockaddr *)&server_addr, LENGHT));
    CheckValue(bind(udp_server_fd, (struct sockaddr *)&server_addr, LENGHT));

    setsockopt(tcp_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &permission_tcp, sizeof(permission_tcp));
    setsockopt(udp_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &permission_udp, sizeof(permission_udp));

    CheckValue(listen(tcp_server_fd, 3));

    FD_ZERO(&set_desc);
    FD_SET(tcp_server_fd, &set_desc);
    FD_SET(udp_server_fd, &set_desc);
    FD_SET(STDIN_FILENO, &set_desc);

    while (1)
    {
        set_desc_copy = set_desc;
        CheckValue(select(FD_SETSIZE, &set_desc_copy, NULL, NULL, &tv));
        for(i = 0; i < FD_SETSIZE; ++i)
        {
            if (FD_ISSET(i, &set_desc_copy))
            {
                if(i == tcp_server_fd)
                {
                    int new_conn;
                    struct sockaddr_in client_addr = {0};
                    fprintf (stderr, "TCP Server is READY\n");
                    new_conn = accept(tcp_server_fd, (struct sockaddr *)&client_addr, &len);
                    CheckValue(new_conn);
                    FD_SET(new_conn, &set_desc);
                }
                if(i == udp_server_fd)
                {


                }
                if(i == STDIN_FILENO)
                {


                }
            }
        }

    }
    









    return 0;
}