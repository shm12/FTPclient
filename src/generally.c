#include "generally.h"

int recv_data(int sockfd, void *buffer, int buffer_size){
	int lenght;

	if ((lenght = recv(sockfd, buffer, buffer_size, 0)) == 0)
	{
		printf("Error: the server close the connection unexpectedly.\n");
		return -3;
	}
	else if (lenght < 0){
		printf("Error: an error occur.\n");
		return -4;
	}
	return lenght;
}

char *getinput(char *final){
	/*
	Biniamin, if you read this, i don't know if it works good
	to realloc the given char arrey (and if yes, should i free it before?). Thank's.
	*/
	int len = 0;
	int tmplen = 200;
	char tmp[tmplen];
	final= NULL;
	while (1){
		if (fgets(tmp, tmplen, stdin) == EOF){
			break;
		}
		len += strlen(tmp) * sizeof(char);
		realloc(final, len);
	}
	return final; 
}