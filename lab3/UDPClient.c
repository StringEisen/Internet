#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define ECHOMAX 255

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in echoServAddr;
	struct sockaddr_in fromAddr;
	unsigned short echoServPort;
	unsigned int fromSize;

	char *servIP;
	char *echoString;
	char echoBuffer[ECHOMAX + 1];

	int echoStringLen;
	int respStringLen;

	if ((argc < 3))
	{
		printf("Usage: %s <Server IP> <Echo Word> [<Echo Port>]\n",
							argv[0]);
		exit(1);
	}

	servIP = argv[1];
	// string to echo
	int i;
	for (i = 2; argv[i] != NULL; i++)
	{
		echoString = echoString + argv[i] + " ";
	}

	if ((echoStringLen = strlen(echoString)) > ECHOMAX)
		printf("Echo word too long.\n");

	if (argc == i+2)
		// parse ASCII string to integer, assign port number
		echoServPort = atoi(argv[i]);
	else 
		echoServPort = 7;// well-known port for echo service

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		printf("socket() failed.\n");

	memset(&echoServAddr, 0, sizeof(echoServAddr));// zero out structure
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = inet_addr(servIP);
	echoServAddr.sin_port = htons(echoServPort);

	if ((sendto(sock, echoString, echoStringLen, 0,
		(struct sockaddr *) &echoServAddr, sizeof(echoServAddr)))
		!= echoStringLen)
        printf("sendto() sent a different number of bytes than expected\n");
	// define the length of from address fromSize
	fromSize = sizeof(fromAddr);
	if ((respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0,
		(struct sockaddr *) &fromAddr, &fromSize)) != echoStringLen)
		printf("recvfrom() failed\n");

	if (echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
	{
		printf("Error : received a packet from unknown source. \n");
		exit(1);
	}
        // null-terminate the string by adding \0 to the end
	echoBuffer[respStringLen] = '\0';
	printf("Received: %s\n", echoBuffer);
	close(sock);
	exit(0);
}
