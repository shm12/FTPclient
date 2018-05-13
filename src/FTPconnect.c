#include <FTPconnect.h>

int FTPconnect(char address[], int port, int* command_sockfd, int* data_sockfd){
//the function gets the server address (in IPv4 !), and it's commands port.
	struct sockaddr_in server_addr;
	char rcv[1024];
	const char success_connect[] = "220"
	const char enter_pasv[] = "227"
	char re_code;
	int lenght;
	int err;

	//set up the server data as a sockaddr_ in struct for use in connect() function.
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	server_addr.sin_addr.s_addr = inet_addr(address);

	//creat socket
	if ((command_sockfd = socket(AF_INET, SOCK_STREAM, 0) == -1){
		printf("Error: could not creat a socket.\n");
		return -1;
	}
	//connect to the server 
	if (connect(command_sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
		printf("Error: could not connect to the server.\n");
		return -2;
	}

	//get server response
	if ((err = recv_data(command_sockfd, (void *) &rcv, sizeof(rcv))) != 0){
		return err;
	}

	rcv = (char *) rcv;
	re_code = get_re_code(rcv);
	if (strcmp(&success_connect, &re_code) != 0)
	{
		printf("Error: the server refuse the request or that it doe's not FTP server.\n");
		return -5;
	}

	//success connecting
	//login
	login(command_sockfd);

	//entering passive mode
	if ((err =send(sockfd, "PASV" , sizeof("PASV"), 0)) == -1){
		printf("Error: can't send data.\n");
		return err;
	}
	if ((err = recv_data(command_sockfd, (void *) &rcv, sizeof(rcv))) != 0){
		return err;
	}
	rcv = (char *) rcv;

	re_code = get_re_code(rcv);
	if (strcmp(&enter_pasv, re_code) != 0){
		printf("Error: an error occur.\n");
		return -5;
	}
	if(err =(enter_pasv_m(rcv, &data_sockfd, server_addr)) != 0){
		return err;
	}
	return 0;
}

int login(int sockfd){

	char rcv[1024];
	char login_success[] = "230";
	char user[24] , name[18] = "anonymous";
	char pass[24] , pswd[18] = "";
	char re_code[4];
	int err;
	while (1){
		user = "USER ";
		pass = "PASS ";
		//send user name
		if ((err =send(sockfd, strcat(&user, &name), sizeof(user), 0)) == -1){
			printf("Error: can't send data.\n");
			return err;
		}
		//get response
		if ((err = (recv_data(sockfd, (void *) &rcv, sizeof(rcv)))) != 0){
			return err;
		}
		//send password
		if ((err = send(sockfd, strcat(&pass, &pswd), sizeof(pass), 0)) == -1){
			printf("Error: can't send data.\n");
			return err;
		}
		//get response
		if ((err = (recv_data(sockfd, (void *) &rcv, sizeof(rcv)))) != 0){
			return err;
		}
		rcv = (char *) rcv;

		re_code = get_re_code(rcv);
		if (strcmp(&re_code, &login_success) == 0){
			break;
		}
		else{
			printf("The server requires login.\n");
			printf("User name: ");
			fgets(&name, sizeof(name),stdin);
			printf("\nPassword: ");
			fgets(&pswd, sizeof(pswd),stdin);
			printf("\n");
		}
	}
	return 0;
}

int recv_data(int sockfd, void *buffer, int buffer_size){
	if ((lenght = recv(command_sockfd, &buffer, buffer_size, 0)) == 0)
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

char* get_re_code(char rcv[]){
	char [4] re_code;
	rcv[3] = "\0";
	strcpy(&re_code, &rcv);
	return re_code;
}

int enter_pasv_m(char rcv[], int* sockfd, struct sockaddr_in server_addr){
	server_addr.sin_port = port_calculate(rcv);
	//creat socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0) == -1){
		printf("Error: could not creat a socket.\n");
		return -1;
	}
	//connect to the server 
	if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
		printf("Error: could not connect to the server.\n");
		return -2;
	}
	return 0;
}

int port_calculate(char rcv[]){
	char cp1[4], cp2[4];
	int p1, p2;
	int i;

	strtok_r(rcv, ")", ",")
	for (i = 0; i < 4; i++){
		strtok_r(NULL, ")", ",")
	}
	strcpy(&cp1, strtok_r(NULL, ")", ","));
	strcpy(&cp2, strtok_r(NULL, ")", ","));
	p1 = atoi(cp1);
	p2 = atoi(cp2);

	return p1*256 + p2;

}
