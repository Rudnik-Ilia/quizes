#pragma once

#define PIPE "./mypipe"
#define BUFFER_SIZE 1024

#define message_pong "P0NG"
#define message_ping "PING"

#define COLOR_red "\033[1;31m" 
#define COLOR_blue "\033[1;34m" 
#define OFFCOLOR "\033[0m" 


int ReadWrite(char* pathname, char *message, int check);