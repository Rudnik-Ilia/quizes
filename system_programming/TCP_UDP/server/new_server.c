#include <stdio.h>         
#include <sys/types.h>     
#include <unistd.h>        
#include <arpa/inet.h>      
#include <stdlib.h>         
#include <string.h>        
#include <time.h>           
#include <sys/select.h>

#include "../header.h"
 
int WORK = 1;

int main()
{
    struct sockaddr_in server_addr = {0};
    int tcp_server_fd = 0;
    int udp_server_fd = 0;
    fd_set set = {0};
    struct timeval tv;
    int record = 1;

    int permission_tcp = 1;
    int permission_udp = 1;

    system("clear");

    Fill_Struct(&server_addr);

    Make_Socket(&tcp_server_fd, 0);
    Make_Socket(&udp_server_fd, 1);

    CheckValue(bind(tcp_server_fd, (struct sockaddr *)&server_addr, LENGHT));
    CheckValue(bind(udp_server_fd, (struct sockaddr *)&server_addr, LENGHT));

    setsockopt(tcp_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &permission_tcp, sizeof(permission_tcp));
    setsockopt(udp_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &permission_udp, sizeof(permission_udp));

    CheckValue(listen(tcp_server_fd, 3));

    FD_ZERO(&set);
    FD_SET(tcp_server_fd, &set);
    FD_SET(udp_server_fd, &set);
    FD_SET(STDIN_FILENO, &set);

    Logger("General server was started!");
    while (WORK)
    {
        int i = 0;
        fd_set set_copy = set;
        tv.tv_sec = 7;
        tv.tv_usec = 0;
        CheckValue(select(FD_SETSIZE, &set_copy, NULL, NULL, &tv));
        
        for (i = 0; i < FD_SETSIZE; ++i)
        {
            if (FD_ISSET(i, &set_copy))
            {
                if (i == tcp_server_fd)
                {
                    int new_conn;
                    struct sockaddr_in client_addr = {0};
                    Logger("Server TCP was started");
                    new_conn = accept (tcp_server_fd, (struct sockaddr*)&client_addr, &len);
                    CheckValue(new_conn);
                    FD_SET(new_conn, &set);
                }
                else if (i == udp_server_fd)
                {
                    struct sockaddr_in client_addr = {0};
                    char buffer[SIZE] = {0};
                    int nbytes;
                    if(record)
                    {
                        Logger("Server UDP was started");
                        record = 0;
                    }
                    nbytes = recvfrom(udp_server_fd, buffer, SIZE, MSG_WAITALL, (struct sockaddr*)&client_addr, &len); 
                    CheckValue(nbytes);
                    fprintf (stderr, "server received %s\n", buffer);
                    nbytes = sendto(udp_server_fd, "pong", SIZE, MSG_CONFIRM, (const struct sockaddr*)&client_addr, LENGHT);
                    CheckValue(nbytes);
                    fprintf (stderr, "server sent %s\n", buffer);
                    
                }
                else if (i == STDIN_FILENO)        
                {
                    char buffer[SIZE + 1] = {0};
                    Logger("Server get message from STDIN");
                    if(record)
                    {
                        Logger("Server UDP was started");
                        record = 0;
                    }
                    read(STDIN_FILENO, buffer, SIZE);
                    if (0 == strcmp(buffer, "ping\n"))
                    {
                        Logger("Server get PING, and send PONG");
                        CheckValue(write(STDOUT_FILENO, "pong\n", SIZE));
                    }
                    if (0 == strcmp(buffer, "quit\n"))
                    {
                        Logger("Server get QUIT command from STDIN");
                        WORK = 0;
                        break;
                    }

                }
                else
                {
                    char buffer[SIZE] = {0};
                    int nbytes;

                    fprintf (stderr, "TCP exsting work\n"); 
                    nbytes = read(i, buffer, SIZE);
                    if (0 == nbytes)
                    {
                        close (i);
                        FD_CLR(i, &set); 
                    }
                    fprintf (stderr, "Server recieve message: %s\n", buffer);
                    nbytes = send(i, "pong", SIZE, MSG_CONFIRM);
                    CheckValue(nbytes);   
                    fprintf (stderr, "Server send message: pong\n");
                }
            }
        }   
    }
    Logger("Server shut down!");
    close(udp_server_fd);
    close(tcp_server_fd);

    return (0);
}
