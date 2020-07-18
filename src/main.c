#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/socket.h>

#include "dhcp.h"

#define PORT 67

int main()
{
	struct sockaddr_in server;

	// Prevents Zombies
	signal(SIGCHLD, SIG_IGN);

	int sock = socket(PF_INET, SOCK_DGRAM, 0);

	int broadcast = 1;
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&broadcast, sizeof(broadcast));
	
	if (sock < 0)
	{
		printf("Error Creating Stream Socket\n");
		return 1;
	}

	server.sin_family      = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port        = htons(PORT);

	int server_size = sizeof(server);

	if (bind(sock, (struct sockaddr *)&server, server_size) < 0)
	{
		printf("Error Binding to socket\n");
		return 2;
	}

	while (1)
	{
		if (fork() == 0)
		{
			close(sock);
			return 0;	
		}
		else
		{
			struct sockaddr_in client;
			unsigned int client_size = sizeof(client);
			int n;

			dhcp_message request;

			if ((n = recvfrom(sock, &request, sizeof(request), 0, (struct sockaddr *)&client, &client_size)) < 0)
			{
				printf("Recieve Error\n");
				return 3;
			}

			print_dhcp_packet(request, client);
		}
	}

	close(sock);
	return 0;
}

