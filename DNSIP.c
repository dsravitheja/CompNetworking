// Ravitheja Dasika
// EE 4272 - Computer Networks

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#define MAXLEN 1025

void checkEndian()
{
	/* PART 1: Check endianness and print message about endianness here. */
	uint32_t a=0x12345678;
    uint32_t b;
    b=htonl(a);
    //printf("the entered value a is %8x and b is %8x\n",a,b);
    printf("Networks use big endian ordering\n");
    if(a == b)
    printf(" This host uses Big Endian\n");
    else
    printf("This host uses little endian \n");

}


int main(int argc, char *argv[])
{
    char name[100];
    printf("enter the address to check\n");
    scanf("%s",&name);
	checkEndian();
    
    char host[MAXLEN];
    char service[30];
	/* The "hints" structure lets us specify exactly what type of
	   address we want to get back from getaddrinfo(). */
	struct addrinfo hints;  // create struct
	memset(&hints, 0, sizeof(hints)); // fill struct with zeros

	// see the getaddrinfo() man page for descriptions of these variables:
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_UNSPEC;
	hints.ai_protocol = 0;
	/* Uncomment this if you only want to resolve the versions of IP that
	   your computer appears to support. For this homework, leave this
	   commented out. */
	// hints.ai_flags = AI_ADDRCONFIG;

    struct sockaddr *sockadd;
   	struct addrinfo *answer, *ans;
	
	socklen_t len;
	int sf;
	int error = getaddrinfo(name, NULL, &hints, &answer);
	if(error != 0)
	{
		fprintf(stderr, "Error in getaddrinfo(): %s\n", gai_strerror(error));
		exit(EXIT_FAILURE);
	}
	/* PART 2 & 3: use information in the variable "answer". */
    else{
    for(ans=answer;ans!=NULL;ans=ans->ai_next)
    {
        sockadd=ans->ai_addr;
        //sockfam= ans->ai_family;
        len= ans->ai_addrlen;
        switch(ans->ai_family) //checking for IPv4 vs IPv6 addresses
        {
        case AF_INET://AF_INET=IPv4
        //printing numeric IP address: Flags NI_NUMERICHOST and NI_NUMERICSERV are set to achieve this
	        if(getnameinfo(ans->ai_addr, ans->ai_addrlen, host, sizeof host, NULL, 0,NI_NUMERICHOST|NI_NUMERICSERV)==0){
	        printf("IPv4: %s\n", host); 
	        }
	        break;
	    case AF_INET6://AF_INET6=IPv6
	    if(getnameinfo(ans->ai_addr, ans->ai_addrlen, host, sizeof host, NULL, 0,NI_NUMERICHOST|NI_NUMERICSERV)==0){
	        printf("IPv6: %s\n", host); 
	        }
	        break;
	        }
	    	    
	    //NI_NAMEREQD is set to output error in finding the address
	    if(getnameinfo(ans->ai_addr, ans->ai_addrlen, host, sizeof host, NULL, 0,NI_NAMEREQD)){
	        printf("Could not find host\n");
	        }
	    //prints reverse DNS lookedup host address
	    else{
	        printf("reverse DNS lookup: %s\n", host);   }
            }
	return 0;
	}
	 
	freeaddrinfo(answer);
}
