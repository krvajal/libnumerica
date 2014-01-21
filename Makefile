
ROOT_DIR := "$(shell pwd)"
CXX  = clang++

CXXFLAGS = -std=c++11 -nostdinc++ -I/Users/Yovi/Documents/libcxx/include  -pedantic -Wall -g -I$(ROOT_DIR)
LDFLAGS  := -L/Users/Yovi/Documents/libcxx/lib -stdlib=libc++ 


TOOLS_HEADERS = $(shell echo numerica/tools/*.h)
TOOLS_SOURCES = $(shell echo numerica/tools/*.cpp)
TOOLS_OBJECTS = $(TOOLS_SOURCES:.cpp=.o)

ROOTS_HEADERS   = $(shell echo numerica/roots/*.h)
ROOTS_SOURCES   :=
ROOTS_OBJECTS   = $(ROOTS_SOURCES:.cpp=.o)

PLOT_SOURCES  =  $(shell echo numerica/plot/*.cpp)
PLOT_HEADERS  =  $(shell echo numerica/plot/*.h)
PLOT_OBJECTS  =  $(PLOT_SOURCES:.cpp=.o)

TESTS_SOURCES = $(shell echo numerica/tests/test_plot.cpp)
TESTS_HEADERS = $(shell echo numerica/tests/*.h)
TESTS_OBJECTS = $(TESTS_SOURCES:.cpp=.o)

all: roots plots tests
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.cpp $(TOOLS_OBJECTS) $(TESTS_OBJECTS) $(PLOT_OBJECTS) -o main

tools: $(TOOLS_OBJECTS)	
	
$(TOOLS_OBJECTS): $(TOOLS_SOURCES) $(TOOLS_HEADERS)


roots: $(ROOTS_OBJECTS)  tools

$(ROOTS_OBJECTS): $(ROOTS_SOURCES)

$(PLOT_OBJECTS): $(PLOT_HEADERS) $(PLOT_SOURCES)	
plots: $(PLOT_OBJECTS) tools



	

$(TESTS_OBJECTS): $(TESTS_SOURCES) $(TESTS_HEADERS) 

tests:  $(TESTS_OBJECTS) tools


	

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@