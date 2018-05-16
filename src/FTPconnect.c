#include "FTPconnect.h"

int FTPconnect(char *address, int port, int* command_sockfd, int* data_sockfd){
//the function gets the server address (in IPv4 !), and it's commands port.
	struct sockaddr_in server_addr;
	char* rcv = (char *) malloc(1024 * sizeof(char));
	const char success_connect[] = "220";
	const char enter_pasv[] = "227";
	char re_code[4];
	int err;

	//set up the server data as a sockaddr_ in struct for use in connect() function.
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(address);

	//creat socket
	if ((*command_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		printf("Error: could not creat a socket.\n");
		return -1;
	}

	//connect to the server 
	if (connect(*command_sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
		printf("Error: could not connect to the server.\n");
		return -2;
	}

	//get server response
	if ((err = recv_data(*command_sockfd, (void *) rcv, 1024)) <= 0){
		return err;
	}

	rcv = (char *)rcv;
	get_re_code(re_code, rcv);
	if (strcmp(success_connect, re_code) != 0){
		printf("Error: the server refuse the request or that it doe's not FTP server.\n");
		return -5;
	}

	//success connecting
	//login
	login(*command_sockfd);

	//entering passive mode
	if ((err =send(*command_sockfd, "PASV\n" , strlen("PASV\n"), 0)) == -1){
		printf("Error: can't send data.\n");
		return err;
	}
	if ((err = recv_data(*command_sockfd, (void *) rcv, 1024)) <= 0){
		return err;
	}
	rcv = (char *)rcv;

	get_re_code(re_code, rcv);
	if (strcmp(enter_pasv, re_code) != 0){
		printf("Error: an error occur.\n");
		return -5;
	}
	if((err =(enter_pasv_m(rcv, data_sockfd, server_addr))) != 0){
		return err;
	}
	return 0;
}

int login(int sockfd){

	char *rcv = (char *) malloc(1024 * sizeof(char));
	char login_success[] = "230";
	char user[strlen("USER ")+18], pass[strlen("PASS ")+18];
	char name[18] = "anonymous\n";
	char pswd[18] = "\n";
	char re_code[4];
	int err;

	while (1){
		strcpy(user, "USER ");
		strcpy(pass, "PASS ");
		//send user name
		if ((err = send(sockfd, strcat(user, name), strlen(user)+strlen(name), 0)) == -1){
			printf("Error: can't send data.\n");
			return err;
		}
		//get response
		if ((err = (recv_data(sockfd, (void *) rcv, 1024))) <= 0){
			return err;
		}
		//send password
		if ((err = send(sockfd, strcat(pass, pswd), strlen(pass)+strlen(pswd), 0)) == -1){
			printf("Error: can't send data.\n");
			return err;
		}
		//get response
		if ((err = (recv_data(sockfd, (void *) rcv, 1024))) <= 0){
			return err;
		}
		rcv = (char *) rcv;

		get_re_code(re_code, rcv);
		if (strcmp(re_code, login_success) == 0){
			break;
		}
		else{
			printf("The server requires login.\n");
			printf("User name: ");
			fgets(name, sizeof(name),stdin);
			printf("Password: ");
			fgets(pswd, sizeof(pswd),stdin);
			printf("\n");
		}
	}
	return 0;
}


char *get_re_code(char *re_code, char *rcv){
	strncpy(re_code, rcv, 3);
	return re_code;
}

int enter_pasv_m(char rcv[], int* sockfd, struct sockaddr_in server_addr){
	if ((server_addr.sin_port = htons(port_calculate(rcv))) == 0){
		printf("Error: an error occur.\n");
		return -3;
	}
	//creat socket
	if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		printf("Error: could not creat a socket.\n");
		return -1;
	}
	//connect to the server 
	if (connect(*sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
		printf("Error: could not connect to the server.\n");
		return -2;
	}
	return 0;
}

int port_calculate(char *rcv){
	char tosplit[strlen(rcv)+1];
	char splitin[] = "),.";
	char cp1[4], cp2[4];
	int p1, p2;
	int i;
	strcpy(tosplit, rcv);

	//begin spliting
	strtok(rcv, splitin);
	for (i = 0; i < 3; ++i){
		strtok(NULL, splitin);
	}
	if ((strcpy(cp1, strtok(NULL, splitin))) == NULL){
		return 0;
	}
	if ((strcpy(cp2, strtok(NULL, splitin))) == NULL){
		return 0;
	}
	p1 = atoi(cp1);
	p2 = atoi(cp2);

	printf("port is: %d\n", (p1*256 + p2));
	return p1*256 + p2;
}
