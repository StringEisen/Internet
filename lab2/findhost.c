#include<stdio.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>

int main (int argc, char *argv[]) {
	struct hostent* h;
	struct in_addr addr;
	char **p;
	
	if (inet_aton(argv[1], &addr) == 0) {
		h = gethostbyname(argv[1]);
	} 
	else {
		h = gethostbyaddr((char *) &addr, 4, AF_INET);
	}
	if (h->h_name != NULL)
		printf("Official name: %s\n", h->h_name);
	
	if (h->h_aliases != NULL)
		for (p = h->h_aliases; *p != NULL; p++)
			printf("Alias: %s\n", *p);
	if (h->h_addrtype != NULL)
		printf("Host address type: %d\n", h->h_addrtype);
	if (h->h_length != NULL)
		printf("Length of address: %d\n", h->h_length);

	if (h->h_addr_list != NULL)
		for (p = h->h_addr_list; *p != NULL; p++)
			printf("address from name server: %s\n", *p);
	if (h->h_addr_list != NULL)
		printf("The first address in the address list: %s\n", 
						h->h_addr_list[0]);

}

		  
