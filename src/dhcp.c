#include <arpa/inet.h>
#include <stdio.h>

#include "dhcp.h"

void print_dhcp_packet(dhcp_message request, struct sockaddr_in client)
{
	printf("Packet:\n");

	printf("\tClient:\n");
	printf("\t\tIP: %s\n", inet_ntoa(client.sin_addr));
	printf("\t\tPort: %d\n", ntohs(client.sin_port));

	printf("\tRequest:\n");
	printf("\t\tOP Code: (%d) %s\n", request.op, op_codes_string[request.op]);
	// TODO: Dynamically get the options
	printf("\t\tOptions: (%d) %s\n", request.options[2], dhcp_message_type_string[request.options[2]]);
	printf("\t\tTransaction ID: 0x%x\n", ntohl(request.xid));
	printf("\t\tServer IP Address: %s\n", inet_ntoa(*((struct in_addr *)&request.siaddr)));
	printf("\t\tOffered IP Address: %s\n", inet_ntoa(*((struct in_addr *)&request.yiaddr)));
	printf("\t\tGateway IP Address: %s\n", inet_ntoa(*((struct in_addr *)&request.giaddr)));

	printf("\n");
}

