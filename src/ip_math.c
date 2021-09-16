#include "ip_math.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

static void print_help();
static void print_commands();
static void call_library_method(const char **argv);
static void print_broadcast_address(const char *ip_address, const char *mask);
static void print_network_id(const char *ip_address, const char *mask);
static void print_integer_ip(const char *ip_address);
static void print_dot_ip(const char *ip_address);
static void print_is_in_subnet(const char *network_id, const char *mask, const char *ip_address);
static void print_subnet_cardinality(uint8_t mask);

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

// TOTEST (explicitly)
void get_dot_ip_format(uint_fast32_t ip_address, char *output_buffer) {
  for (int i = 24; i >= 0; i-=8) {
    const int bytes_written = sprintf(output_buffer, "%hhu", (uint8_t)(ip_address >> i));
    output_buffer += bytes_written;

    if (i > 0) {
      *output_buffer = '.';
      output_buffer ++;
    }
  }
}

// TOTEST
uint_fast32_t get_subnet_cardinality(uint8_t mask) {
  return pow(2, mask) - 2;
}

// TODO
bool is_ip_in_subnet(char *network_id, uint8_t mask, char* ip_address) {
  return 0;
}

void get_network_id(char *ip_address, uint8_t mask, char *output_buffer) {
  uint_fast32_t integer_ip = get_ip_integer_equivalent(ip_address);
  uint_fast32_t integer_network_id = (integer_ip >> mask) << mask;
  get_dot_ip_format(integer_network_id, output_buffer);
}

int main(int argc, const char **argv) {
  if (argc == 2) {
    strcmp(argv[1], "help") == 0 ? print_help() : print_commands();
  }
  else if (argc == 3 || argc == 4)
    call_library_method(argv);
  else
    print_commands();

  return 0;
}

// TODO update with new commands
static void print_help() {
  printf("Examples of each command are as follows: \n");
  printf("broadcast 192.168.1.1 24\n");
  printf("integer 192.168.1.1\n");
}

static void print_commands() {
    printf("Possible commands are: broadcast, integer, help\n");
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
  else if(strcmp(method_name, "hosts") == 0)
    print_dot_ip(argv[2]);
  else
    print_commands();
}

static void print_broadcast_address(const char *ip_address, const char *mask) {
    char output[16] = {};
    uint8_t broadcast = strtol(mask, NULL, 10);

    get_broadcast_address(ip_address, broadcast, output);
    printf("broadcast address: %s\n", output);
}

static void print_integer_ip(const char *ip_address) {
  printf("integer ip address: %lu\n", get_ip_integer_equivalent(ip_address));
}

// TODO
static void print_subnet_cardinality(uint8_t mask) {

}

// TODO
static void print_network_id(const char *ip_address, const char *mask) {

}

// TODO
static void print_dot_ip(const char *ip_address) {

}

// TODO
static void print_is_in_subnet(const char *network_id, const char *mask, const char *ip_address) {

}
