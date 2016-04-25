#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/*



Datatypes:
---------

struct addrinfo {
   int              ai_flags;
   int              ai_family;
   int              ai_socktype;
   int              ai_protocol;
   socklen_t        ai_addrlen;
   struct sockaddr *ai_addr;
   char            *ai_canonname;
   struct addrinfo *ai_next;
};

*/


static int
create_and_bind (char *port)
{
	struct addrinfo hints;
	struct addinfo *results, *rp;
	int sfd, s;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC; /* Return IPv4 and IPv6 choices */
	hints.ai_socktype = SOCK_STREAM; /* TCP Socket */
	hints.ai_flags = AI_PASSIVE; /* All interfaces */
	
	/* Allows programs to eliminate IPv4-versus-IPv6 dependencies */
	/* Store the addrinfo in result*/
	s = getaddrinfo(NULL, port, &hints, &results);
	if (s != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror (s));
		return -1;
	}
	
	for (rp = results; rp != NULL; rp = rp->ai_next)
	{
		sfd = socket (rp->ai_family, rp->ai_sockettype, rp->ai_protocol);
		
		if (sfd == -1)
			continue;
		
	}
}


void main(int argc, char *argv[])
{
	
	// Create Socket
	int infd = create_and_bind("1234");

	// Bind Socket
	int outfd = bind_socket(infd)
	
	// Listen on Socket
	int r = listen(outfd)
	
	// Accept Socket	

}