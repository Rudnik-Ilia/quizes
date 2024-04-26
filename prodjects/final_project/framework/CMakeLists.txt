cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME first)
set(CMAKE_CXX_FLAGS "-Wall -o2")
 

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

project(${PROJECT_NAME})

set(SOURCES src/main.cpp)

set(HEADERS src/head.hpp)

# file(GLOB 
#         CPPS "*.cpp")

message(${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

add_library(my_lib SHARED src/head.hpp src/lib.cpp) 


target_link_libraries(${PROJECT_NAME} PRIVATE my_lib)

# target_include_directories(${PROJECT_NAME} PRIVATE path....)
# include_directories() for all targets

#  install( LIBRARY DESTINATION lib INCLUDE DESTINATION include)