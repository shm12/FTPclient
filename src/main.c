#include "main.h"


int main(int argc, char const *argv[])
{
	char *address = (char *) malloc(1024 * sizeof(char));
	char pr[6];
	char usage[] = "Usage: <name of th program> <hostnam> [port].\nNote: port 21 is default.";//need to be writen yet
	int command_sockfd, data_sockfd;
	unsigned  port;
	char* command;
	int err;

	if (argc == 3){
		strcpy(address, argv[1]);
		strcpy(pr,argv[2]);
	}
	else if(argc == 2){
		strcpy(address, argv[1]);
		strcpy(pr, "21");
	}
	else{
		printf("%s\n", usage);
	}

	//get ipv4 address
	/*
	if ((address = getip(address)) == NULL)
	{
		printf("Exiting...\n");
		return -6;
	}
	*/

	//get port (if bigger than 2^16-1 (65535 - the highest port) it will be int overflow)
	if ((port = atoi(pr))== 0){
		printf("Error: no valid port.\n");
		return -7;
	}

	//connect
	if ((err = (FTPconnect(address, port, &command_sockfd, &data_sockfd))) != 0){
		printf("Exiting...\n");
		close(command_sockfd);
		close(data_sockfd);
		return err;
	}

	while (1){
		
	}

	return 0;
}


char *getip(char *hostname){
	struct hostent *hostinf;
	struct hostent tmp;
	{
		
	};
	int type;

	hostinf = gethostbyname(hostname);
	tmp = *hostinf;
	if (!hostinf){
		printf("Error: could not find the server.\n");
		return NULL;
	}
	type = tmp.h_addrtype; 
	if (type == AF_INET)
	{
		strcpy(hostname, (*hostinf->h_addr));
		return hostname;
	}
	
	return NULL;
}


/* still at work, not for compile yet

char **split_to_args(char **args, char *line){

	int lslen = 0;
	char tmp[];
	int i = 1;

	if((tmp = strtok(line, " ")) == NULL){
		
	}
}

*/
