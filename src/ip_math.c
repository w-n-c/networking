#include "ip_math.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static void call_library_method(const char **argv);
static void print_help();
static void print_commands();
static void print_broadcast_address(const char *ip_address, const char *mask);
static void print_network_id(const char *ip_address, const char *mask);
static void print_integer_ip(const char *ip_address);
static void print_dot_ip(const char *ip_address);
static void print_is_in_subnet(const char *network_id, const char *mask, const char *ip_address);
static void print_subnet_cardinality(const char *mask);

void get_broadcast_address(const char *ip_address, uint8_t mask, char *output_buffer) {
  uint_fast32_t integer_ip = get_ip_integer_equivalent(ip_address);
  uint_fast32_t bit_mask = UINT32_MAX >> mask;
  uint_fast32_t integer_broadcast = integer_ip | bit_mask;
  get_dot_ip_format(integer_broadcast, output_buffer);
}

uint_fast32_t get_ip_integer_equivalent(const char *ip_address) {
  const uint_fast8_t segment_count = 4;
  uint_fast32_t integer_ip = 0;
  uint8_t parsed_value;

  for (uint_fast8_t i = 0; i < segment_count; i++) {
    sscanf(ip_address, "%3hhu", &parsed_value);
    integer_ip |= parsed_value;

    if (i != segment_count - 1) {
      integer_ip <<= 8;
      while(*ip_address++ != '.');
    }
  }

	return integer_ip;
}

void get_dot_ip_format(const uint_fast32_t ip_address, char *output_buffer) {
  for (int i = 24; i >= 0; i-=8) {
    const int bytes_written = sprintf(output_buffer, "%hhu", (uint8_t)(ip_address >> i));
    output_buffer += bytes_written;

    if (i > 0) {
      *output_buffer = '.';
      output_buffer ++;
    }
  }
}

uint_fast32_t get_subnet_cardinality(uint8_t mask) {
  return (1 << (32 - mask)) - 2;
}

bool is_ip_in_subnet(const char *network_id, const uint8_t mask, const char* ip_address) {
  const uint_fast32_t int_network_id = get_ip_integer_equivalent(network_id);
  const uint_fast32_t cardinality = get_subnet_cardinality(mask);
  const uint_fast32_t int_ip_address = get_ip_integer_equivalent(ip_address);
  const uint_fast32_t int_broadcast_ip = int_network_id + cardinality + 1;
  return int_ip_address > int_network_id && int_ip_address < int_broadcast_ip;
}

void get_network_id(const char *ip_address, const uint8_t mask, char *output_buffer) {
  uint_fast32_t integer_ip = get_ip_integer_equivalent(ip_address);
  uint_fast32_t integer_network_id = (integer_ip >> mask) << mask;
  get_dot_ip_format(integer_network_id, output_buffer);
}

int main(int argc, const char **argv) {
  if (argc == 2)
    strcmp(argv[1], "help") == 0 ? print_help() : print_commands();
  else
    call_library_method(argv);
  return 0;
}

static void print_help() {
  printf("Examples of each sub-command are as follows: \n");
  printf("in_subet 192.168.1.0 24 192.168.1.12\n"
  "broadcast 192.168.1.1 24\n"
  "network 192.168.1.8 24\n"
  "dot 2058138165\n"
  "cardinality 24\n"
  "integer 192.168.1.1\n");
}

static void print_commands() {
    printf("Possible sub-commands are: in_subnet, broadcast, network, "
    "integer, dot, cardinality, help\n");
}

static void call_library_method(const char **argv) {
  const char *method_name = argv[1];
  if(strcmp(method_name, "in_subnet") == 0)
    print_is_in_subnet(argv[2], argv[3], argv[4]);
  else if (strcmp(method_name, "broadcast") == 0)
    print_broadcast_address(argv[2], argv[3]);
  else if(strcmp(method_name, "network") == 0)
    print_network_id(argv[2], argv[3]);
  else if(strcmp(method_name, "integer") == 0)
    print_integer_ip(argv[2]);
  else if(strcmp(method_name, "dot") == 0)
    print_dot_ip(argv[2]);
  else if(strcmp(method_name, "cardinality") == 0)
    print_subnet_cardinality(argv[2]);
  else {
    printf("command %s not found\n", method_name);
    print_commands();
  }
}

static void print_broadcast_address(const char *ip_address, const char *mask) {
    char output[16] = {};
    uint8_t broadcast = atoi(mask);

    get_broadcast_address(ip_address, broadcast, output);
    printf("broadcast address: %s\n", output);
}

static void print_integer_ip(const char *ip_address) {
  printf("integer ip address: %lu\n", get_ip_integer_equivalent(ip_address));
}

static void print_subnet_cardinality(const char *mask) {
  const uint8_t int_mask = atoi(mask);
  printf("subnet of size %s contains %lu available ip adresses\n",
    mask,
    get_subnet_cardinality(int_mask));
}

static void print_network_id(const char *ip_address, const char *mask) {
  char output[16] = {};
  const uint8_t int_mask = atoi(mask);
  get_network_id(ip_address, int_mask, output);
  printf("network id: %s", output);
}

static void print_dot_ip(const char *ip_address) {
  char output[16] = {};
  uint_fast32_t integer_ip = atoi(ip_address);
  get_dot_ip_format(integer_ip, output);
  printf("dot ip address: %s\n", output);
}

static void print_is_in_subnet(const char *network_id, const char *mask, const char *ip_address) {
  const uint8_t int_mask = atoi(mask);
  const bool is_in_subnet = is_ip_in_subnet(network_id, int_mask, ip_address);
  const char *print_negate_statement = is_in_subnet ? "" : " not";
  printf("ip address %s is%s in network %s/%s\n",
    ip_address,
    print_negate_statement,
    network_id,
    mask);
}
