#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h> // for sockaddr_in and inet_ntoa()
#include<stdlib.h> // for atoi() and exit()
#include<string.h> // for memset()
#include<unistd.h> // for close()

#define ECHOMAX 255

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in echoServAddr;
	struct sockaddr_in echoClntAddr;
	unsigned int cliAddrLen;
	char echoBuffer[ECHOMAX];
	unsigned short echoServPort;
	unsigned short cliPort;
	int recvMsgSize;

	if (argc != 2)
	{
		printf("Usage: %s <UDP SERVER PORT>\n", argv[0]);
		exit(1);
	}

	echoServPort = atoi(argv[1]);
	 
	if ((sock = socket(PF_INET,SOCK_DGRAM, 0)) < 0)
		printf("socket() failed.\n");

	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	echoServAddr.sin_port = htons(echoServPort);

	if ((bind(sock, (struct sockaddr *) &echoServAddr, 
		sizeof(echoServAddr))) < 0)
		printf("bind() failed.\n");

	for (;;)
	{
		cliAddrLen = sizeof(echoClntAddr);
		cliPort = echoClntAddr.sin_port;
		// block until receive message from a client
		if ((recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX,
			0, (struct sockaddr *) &echoClntAddr, &cliAddrLen)) < 0)
			printf("recvform() failed.\n");
 	// print handling message
		int i;
		for (i = 0; i < strlen(echoBuffer); i++)
	printf("%s: from %s: UDP%s: echoBuffer[i]\n",argv[0], inet_ntoa(echoClntAddr.sin_addr), (char *)&cliPort);
	
	if ((sendto(sock, echoBuffer, recvMsgSize, 0,
		(struct sockaddr *) &echoClntAddr,
		sizeof(echoClntAddr))) != recvMsgSize)
	printf("sendto() sent a different number of bytes than expected.\n");
	}
}
