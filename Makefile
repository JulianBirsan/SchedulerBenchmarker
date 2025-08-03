CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I/usr/local/include
LDFLAGS = -L/usr/local/lib

# Tests main files
TESTS_MAIN_SRCS = tests/main.cc tests/test_driver.cc src/thread.cc src/simulator.cc examples/schedulers/round_robin.cc examples/schedulers/mlfq.cc
TESTS_MAIN_OBJS = $(TESTS_MAIN_SRCS:.cc=.o)

# Targets
all: tests_main

tests_main: $(TESTS_MAIN_OBJS)
	$(CXX) $(TESTS_MAIN_OBJS) -o $@ $(LDFLAGS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TESTS_MAIN_OBJS) tests_main

.PHONY: all clean tests_main 