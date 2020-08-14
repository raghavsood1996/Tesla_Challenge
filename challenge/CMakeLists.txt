cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


set(CMAKE_CXX_FLAGS "-Wall -Wextra -msse3 -Ofast")

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Ofast")



project(SuperCharger)
include_directories(include)

link_directories(/usr/local/lib)


add_executable (super_charger source/main.cpp source/network.cpp source/search.cpp )



set_property(TARGET super_charger PROPERTY CXX_STANDARD 20)
