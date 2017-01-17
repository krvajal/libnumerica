cmake_minimum_required(VERSION 2.8.7)

project(numerica_sample)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCES ../main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/../../)
add_executable(numerica_sample ${SOURCES})
target_link_libraries(numerica_sample libnumerica)
