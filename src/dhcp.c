#include <arpa/inet.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "dhcp.h"

char * mac_string(u_int8_t * mac)
{
	char * mac_as_string = malloc(16);

	sprintf(mac_as_string, "%02X:%02X:%02X:%02X:%02X:%02X",
	mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

	return mac_as_string;
}

void print_dhcp_packet(dhcp_message request, struct sockaddr_in client)
{
	printf("Packet:\n");

	printf("\tClient:\n");
	printf("\t\tIP: %s\n", inet_ntoa(client.sin_addr));
	printf("\t\tPort: %d\n", ntohs(client.sin_port));
	char * mac_str = mac_string(request.chaddr);
	printf("\t\tClient MAC Address: %s\n", mac_str);
	free(mac_str);

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

