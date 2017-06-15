#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

// Final exam for Systems - Jacob Beiter
// with inspiration from echo_client_refactored.c mentioned at the review

//try to connect with host & port - return null if fail
FILE* scan(const char *host, const char *port)
{
    struct addrinfo *results;
   struct addrinfo hints = {
   .ai_family = AF_INET,
   .ai_socktype = SOCK_STREAM,
   };
    
    int status = getaddrinfo(host,port,&hints,&results);

    if(status != 0)
    {
	fprintf(stderr, "getaddrinfo failed: %s\n", gai_strerror(status));
	return NULL;
    }

    //try each server entry
    int client_fd = -1;
    for(struct addrinfo *p = results; p != NULL && client_fd < 0 ;p = p->ai_next)
    {
	client_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if(client_fd < 0)
	{
	    fprintf(stderr,"Couldn't make socket: %s\n",strerror(errno));
	    continue;
	}

	if(connect(client_fd, p->ai_addr, p->ai_addrlen) < 0)
	{
	    close(client_fd);
	    client_fd = -1;
	    continue;
	}
    }

    freeaddrinfo(results);

    if(client_fd < 0)
	return NULL;

    FILE *client_file = fdopen(client_fd, "w+");
    if(client_file == NULL)
    {
	close(client_fd);
	return NULL;
    }
    fprintf(stdout,"Connected to port %s\n",port);
    return client_file;
}

int main()
{
    FILE* oraclefd;
    char port[] = "9999";

    for(int i = 9700; i <= 9799; i++)
    {
	sprintf(port,"%d",i);
	oraclefd = scan("xavier.h4x0r.space",port); 

	if(oraclefd != NULL)
	    break;
    }

    struct stat s;
    stat("final.c",&s);

    fprintf(oraclefd,"PUT jbeiter %d\n",(int)s.st_size);

    FILE* sourcefd = fopen("final.c","r");

    char buffer[BUFSIZ];
    while(fgets(buffer, BUFSIZ, sourcefd))
    {
	fputs(buffer,oraclefd);
    }

    fclose(oraclefd);
    fclose(sourcefd);
    return 0;
}
