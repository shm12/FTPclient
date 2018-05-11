#include <FTPconnect.h>

int FTPconnect(char address[], int port){//the function gets the server address (in IPv4 !), and it's commands port
	int sockfd;
	struct sockaddr_in server_addr;
	char recv[1024];

	//set up the server data as a sockaddr_ in struct for use in connect() function.
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	server_addr.sin_addr.s_addr = inet_addr(address);

	//creat socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0) == -1){
		printf("Error: could not creat a socket.\n");
		return -1;
	}
	//connect to the server 
	if (connect(sockfd, (struct sockaddr *) &server_addr, size_of(server_addr)) < 0){
		printf("Error: could not connect to the server.\n");
		return -2;
	}
	//TO DO FOR NOW: recv 220 from server, connect via passiv mode (if we don't want to creat server side as well..) and return to main.
}