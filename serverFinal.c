// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>
#define PORT 12163
int main(int argc, char const *argv[])
{
	int n;
	int pid;

	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Message from server.";
	char *msg = "";
	
	// Creating socket file descriptor
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	//printf("server_fd = %d \n", server_fd);
	// AF_INET means use IPv4
	// SOCK_STREAM means reliable two-way connection byte stream
	// lookat linux man socket(2)

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	//printf("address.sin_family = %d \n", address.sin_family);
	//printf("address.sin_addr.s_addr = %d \n", address.sin_addr.s_addr);	
	//printf("address.sin_port = %d \n", address.sin_port);

	// sin_family is 2, which is what corresponds to AF_INET which goes to IPv4
	// sin_addr is 0 because INADDR_ANY is a built in thing to represent all interfaces
	// sin_port is just the port # translated to network byte order. 12163 -> 33583


	bind(server_fd, (struct sockaddr *)&address, sizeof(address) );
	
	listen(server_fd, 3);


	while(1)
	{

		new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
		pid = fork();

		if(pid==0)
		{
			while(1)
			{
				n=recv(new_socket, buffer, 1024, 0);
				if(n==0)
				{
					close(new_socket);
					break;
				}
				buffer[n]=0;
				//send(new_socket,hello,n,0);
				printf("Received: %s\n", buffer);
				//printf("Sent: %s\n", hello);



			}
			exit(0);
		}
		else
		{
			close(new_socket);
			//printf("Socket Closed.\n");
			//waitpid(pid);
		}
		//return 0;
	}
	
	
	//return 0;
} 










