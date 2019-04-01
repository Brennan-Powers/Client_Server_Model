
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#define PORT 12163

int main(int argc, char const *argv[])
{
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char buffer[1024] = {0};
	char message[100];

	sock = socket(AF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address\n");
		return -1;
	}
	

	connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	while(1)
	{
		printf("Enter your message to send to the server:\n");
		fgets(message,100,stdin);

		send(sock , message , strlen(message) , 0);
		printf("Sent: %s\n", message);
		//printf("Recieved: %s\n", buffer);
		//valread = read( sock , buffer, 1024);
		//printf("Recieved: %s\n", buffer);
	}

	//while(1)
	//{
		//just here to hold client connection
	//}

	return 0;
}

