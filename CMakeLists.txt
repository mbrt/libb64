CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT("libb64")

set(BUFFER_SIZE "16777216" CACHE STRING "Buffer size: a larger size should be faster, but takes more runtime memory")

include_directories("include")
add_library(b64 STATIC src/cdecode.c src/cencode.c)

add_definitions(-DBUFFERSIZE=${BUFFER_SIZE})
add_executable(base64 base64/base64.cc)
target_link_libraries(base64 b64)
