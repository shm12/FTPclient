#include <main.h>


int main(int argc, char const *argv[])
{
	char address[], prt[];
	char usage[];//need to be writen yet
	int command_sockfd, data_sockfd;
	int port;
	int err;

	if (argc == 3){
		domain[] = &argv[1];
		prt[] = argv[2];
	}
	else if(argc == 2){
		domain[] = argv[1];
		prt[] = "21"
	}
	else{
		printf("%s\n", usage);
	}

	//TO DO: convert hostname to ip, port to int, write usage.
	
	//connect
	if (err = (FTPconnect(address, port, &command_sockfd, &data_sockfd)) != 0){
		printf("exiting...\n");
		return err;
	}

	return 0;
}