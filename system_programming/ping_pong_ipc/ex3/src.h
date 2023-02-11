#pragma once

#define PIPE "./mypipe"
#define BUFFER_SIZE 1024

#define message_pong "P0NG"
#define message_ping "PING"

int ReadWrite(char* pathname, char *message, int check);