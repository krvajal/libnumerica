project(libnumerica)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES
        bases/algorithm.h
        roots/bisection.h
        roots/brent.h
        roots/muller.h
        roots/newton.h
        roots/rootlocalizer.h
        roots/roots.h
        roots/secant.h
        tools/constants.h
        tools/mathfunctions.h
        tools/nmatrix.cpp
        tools/nmatrix.h
        tools/nvector.cpp
        tools/nvector.h
        tools/tools.h
        tools/utils.cpp
        tools/exceptions/InvalidArgumentException.cpp
        tools/exceptions/InvalidArgumentException.h
        tools/utils.hpp
        integration/integration.h
        integration/simpson.cpp
        integration/trapezoidal.cpp
        integration/trapezoidal.h
        integration/simpson.h
        numerica.h)
include_directories(..)

add_library(libnumerica SHARED ${SOURCE_FILES})
