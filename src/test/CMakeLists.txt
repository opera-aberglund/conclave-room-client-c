cmake_minimum_required(VERSION 3.17)
enable_testing()

set(CMAKE_C_STANDARD 99)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(isDebug TRUE)
else()
  set(isDebug FALSE)
endif()

if(isDebug)
  message("Debug build detected")
  add_compile_definitions(CONFIGURATION_DEBUG TYRAN_CONFIGURATION_DEBUG)
  set(CONFIGURATION_DEBUG 1)
endif()

add_executable(conclave-room-client-test main.c test.c)

add_test(NAME conclave-room-client-test COMMAND conclave-room-client-test)

if(WIN32)
  target_link_libraries(conclave-room-client-test conclave-room-client )
else()
  target_link_libraries(conclave-room-client-test conclave-room-client  m)
endif(WIN32)
