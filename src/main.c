#include <main.h>


int main(int argc, char const *argv[])
{
	char domain[], port[];
	if (argc => 3){
		domain[] = &argv[1];
		port[] = argv[2];
	}
	else if(argc == 2){
		domain[] = argv[1];
		port[] = "21"
	}
	//TO DO FOR NOW: call to FTPconnect functoin
	return 0;
}