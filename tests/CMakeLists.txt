

project(test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(TEST_SOURCES main.cpp test_roots.cpp)
include_directories( . )
add_executable(tests ${TEST_SOURCES})

target_link_libraries(tests numerica)
