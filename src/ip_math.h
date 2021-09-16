#include <inttypes.h>
#include <stdbool.h>

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
void get_broadcast_address(const char *ip_address, uint8_t mask, char *output_buffer);

/*
 * USAGE:
 * char *ip_address = "192.168.2.10";
 * unsigned int integer_ip = get_ip_integer_equivalent(ip_address);
 * printf("Integer equivalent for %s is %u\n", ip_address, integer_ip);
 * EX: 192.168.2.10 -> 3_232_236_042
 * EX: 10.1.23.10 -> 167_843_594
 */
uint_fast32_t get_ip_integer_equivalent(const char *ip_address);

/*
 * USAGE:
 * unsigned int int_ip = 2058138165;
 * char ip_address_buffer[PREFIX_LENGTH];
 * memset(ip_address_buffer, 0, PREFIX_LENGTH);
 * get_dot_ip_format(int_ip, ip_address_buffer);
 * printf("IP address in A.B.C.D format is %s\n", ip_address_buffer);
 * EX: 2058138165 -> 122.172.178.53
 */
void get_dot_ip_format(uint_fast32_t ip_address, char *output_buffer);

/*
 * USAGE:
 * char network_id_buffer[PREFIX_LENGTH];
 * memset(ip_address_buffer, 0, PREFIX_LENGTH);
 * char *ip_address = "192.168.2.10";
 * uint8_t mask = 20;
 * get_network_id(ip_address, mask, network_id_buffer);
 * printf("Network id is %s\n");
 * EX: 192.168.1.1 24 -> 129.168.0.0
 * EX: 10.1.23.10 20 -> 10.1.16.0
 */
void get_network_id(char *ip_address, uint8_t mask, char *output_buffer);

/*
 * USAGE:
 * unsigned char mask = 24;
 * printf("Subnet cardinality for mask = %u is %u\n", mask, get_subnet_cardinality(mask));
 * EX: 24 -> 254
 * EX: 30 -> 2
 */
void get_subnet_cardinality(uint8_t mask);

/*
 * USAGE:
 * char *network_id = "192.168.0.0";
 * char mask = 24;
 * char *check_ip = "192.168.0.13"
 * bool is_in_subnet = is_ip_in_subnet(network_id, mask, check_ip);
 * char* conditional = (is_in_subnet) ? "" : " not";
 * printf("IP address %s is%s a member of subnet %s/%u\n", check_ip, conditional, network_id, mask);
 * EX: 192.168.0.0 24 192.168.0.13 -> true
 * EX: 192.168.0.0 24 192.169.0.13 -> false
 */
bool is_ip_in_subnet(char *network_id, uint8_t mask, char* ip_address);
