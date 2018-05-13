#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int FTPconnect(char address[], int port, int* command_sockfd, int* data_sockfd);

int login(int sockfd);

int recv_data(int sockfd, void *buffer, int buffer_size);

char* get_re_code(char rcv[]);

int enter_pasv_m(char rcv[], int* sockfd, struct sockaddr_in server_addr);

int port_calculate(char rcv[]);