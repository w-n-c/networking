cmake_minimum_required(VERSION 3.2)
project(Networking LANGUAGES C)

include_guard()
enable_testing()
cmake_policy(SET CMP0110 NEW)

#add_library(ip_math ip_math.c)
add_executable(ip_math ip_math.c)

add_test(NAME integerIp1
  COMMAND ip_math integer 192.168.2.10
)

set_tests_properties(integerIp1 PROPERTIES
  PASS_REGULAR_EXPRESSION "3232236042"
)

add_test(NAME integerIp2
  COMMAND ip_math integer 10.1.23.10
)

set_tests_properties(integerIp2 PROPERTIES
  PASS_REGULAR_EXPRESSION "167843594"
)

add_test(NAME broadcastMask24
  COMMAND ip_math broadcast 192.168.1.1 24
)

set_tests_properties(broadcastMask24 PROPERTIES
  PASS_REGULAR_EXPRESSION "192\.168\.1\.255"
)

add_test(NAME broadcastMask20
  COMMAND ip_math broadcast 10.1.23.10 20
)

set_tests_properties(broadcastMask20 PROPERTIES
  PASS_REGULAR_EXPRESSION "10\.1\.31\.255"
)

add_test(NAME dotIp
  COMMAND ip_math dot 2058138165
)

set_tests_properties(dotIp PROPERTIES
  PASS_REGULAR_EXPRESSION "122\.172\.178\.53"
)
