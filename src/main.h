#include "FTPconnect.h"
#include <unistd.h>
#include <netdb.h>

char *getip(char *hostname);

char **split_to_args(char **args, char *line);