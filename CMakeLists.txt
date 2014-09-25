CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT("libb64" C)

include_directories("include")
add_library(b64 STATIC src/cdecode.c src/cencode.c)
