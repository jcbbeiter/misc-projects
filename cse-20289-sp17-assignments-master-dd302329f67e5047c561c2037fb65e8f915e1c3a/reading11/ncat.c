#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void usage(int exit_status)
{
    puts("Usage: ./ncat HOST PORT");
    exit(exit_status);
}

int main(int argc, char* argv[])
{
    if(argc < 3)
	usage(1);

    char* HOST = argv[1];
    char* PORT = argv[2];

    struct addrinfo hints = {
    .ai_family = AF_INET,
    .ai_socktype = SOCK_STREAM,
    };

    struct addrinfo* res;

    int result = getaddrinfo(HOST,PORT,&hints,&res);

    if(result)
    {
	fprintf(stderr,"getaddrinfo: %s\n",gai_strerror(result));
	exit(1);
    }

    int sockfd = -1 ;

    //tries all of the results in res until successful connection
    for(struct addrinfo *p = res; p!= NULL && sockfd < 0; p = p-> ai_next)
    {
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0)
	{
	    fprintf(stderr,"socket: %s\n",strerror(errno));
	    continue;
	}

	result = connect(sockfd,p->ai_addr,p->ai_addrlen);

	if(result < 0)
	{
	    fprintf(stderr,"Failed to connect to %s:%s : %s\n",HOST,PORT,strerror(errno));
	    close(sockfd);
	    sockfd = -1;
	    continue;
	}
    }
    
    freeaddrinfo(res);

    FILE *fd = fdopen(sockfd, "w+");

    if(fd == NULL)
    {
	fprintf(stderr, "unable to fdopen: %s\n",strerror(errno));
	close(sockfd);
	exit(1);
    }

    char buffer[BUFSIZ];
    while(fgets(buffer, BUFSIZ, stdin))
    {
	fputs(buffer,fd);
	fflush(fd);
    }

    close(sockfd);
    fclose(fd);

    return 0;
}
