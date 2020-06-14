cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


set(CMAKE_CXX_FLAGS "-Wall -Wextra -msse3 -Ofast")

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Ofast")



project(SuperCharger)
include_directories(include)


link_directories(/usr/local/lib)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(Gperftools)

include_directories(SYSTEM ${GPERFTOOLS_INCLUDE_DIR} )
add_executable (super_charger source/main.cpp source/network.cpp source/search.cpp )
target_link_libraries(super_charger ${GPERFTOOLS_LIBRARIES})


set_property(TARGET super_charger PROPERTY CXX_STANDARD 20)
