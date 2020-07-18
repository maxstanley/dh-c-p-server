#ifndef DHCP_H
#define DHCP_H

#include <stdint.h>

// Options 53 - DHCP Message Type
// Page 14 - rfc2131
typedef enum {
	DHCPDISCOVER = 1,
	DHCPOFFER = 2,
	DHCPREQUEST = 3,
	DHCPACK = 4,
	DHCPNAK = 5,
	DHCPDECLINE = 6,
	DHCPRELEASE = 7,
	DHCPINFORM = 8,
} dhcp_message_type;

static const char * const dhcp_message_type_string[] = {
	[DHCPDISCOVER] = "DHCPDISCOVER",
	[DHCPOFFER] = "DHCPOFFER",
	[DHCPREQUEST] = "DHCPREQUEST",
	[DHCPACK] = "DHCPACK",
	[DHCPNAK] = "DHCPNAK",
	[DHCPDECLINE] = "DHCPDECLINE",
	[DHCPRELEASE] = "DHCPRELEASE",
	[DHCPINFORM] = "DHCPINFORM",
};

typedef enum {
	BOOTREQUEST = 1,
	BOOTREPLY = 2,
} op_codes;

static const char * const op_codes_string[] = {
	[BOOTREQUEST] = "BOOTREQUEST",
	[BOOTREPLY] = "BOOTREPLY",
};

// https://w1.fi/wpa_supplicant/devel/structdhcp__message.html
// dhcp_message type
typedef struct {
	u_int8_t op; // Message op code
	u_int8_t htype;
	u_int8_t hlen;
	u_int8_t hops;
	
	u_int32_t xid;
	
	u_int16_t secs;
	u_int16_t flags;
	
	u_int32_t ciaddr;
	u_int32_t yiaddr;
	u_int32_t siaddr;
	u_int32_t giaddr;
			   
	u_int8_t chaddr [16];
	u_int8_t sname [64];
	u_int8_t file [128];

	u_int32_t cookie;
	u_int8_t options [312];
} dhcp_message;

void print_dhcp_packet(dhcp_message packet, struct sockaddr_in client);

#endif
