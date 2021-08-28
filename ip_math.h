/*
 * USAGE:
 * char ipadddress_buffer[PREFIX_LENGTH]; // (16)
 * memset(ip_address_buffer, 0, PREFIX_LENGTH);
 * char *ip_address = "192.168.2.10";
 * char mask = 20;
 * get_broadcast_address(ip_address, mask, ip_address_buffer);
 * printf("Broadcast address = %s\n", ip_address_buffer);
 * EX: 192.168.1.1, 24 -> 192.168.1.255
 * EX: 10.1.23.10, 20 -> 10.1.31.255
 */ 
void get_broadcast_address(char *ip_address, char mask, char output_buffer);

/*
 * USAGE:
 * char *ip_address = "192.168.2.10";
 * unsigned int integer_ip = get_ip_integer_equivalent(ip_address);
 * printf("Integer equivalent for %s is %u\n", ip_address, integer_ip);
 * EX: 192.168.2.10 -> 3_232_236_042
 * EX: 10.1.23.10 -> 167_843_594
 */
unsigned int get_ip_integer_equivalent(char *ip_address);
