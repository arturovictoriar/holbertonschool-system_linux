#ifndef API_H
#define API_H

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define NUM_CLNTS 16
#define BUFFER_SIZE 8192
#define CRLF "\xD\xA"
#define SP "\x20\x9"

int parse_req(char *req);
void client_res(int socket_client, int status);
void err_socket(char *msg);

#endif
