CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I/usr/local/include
LDFLAGS = -L/usr/local/lib

# Source files
SRCS = src/main.cc src/thread.cc src/simulator.cc examples/schedulers/round_robin.cc
OBJS = $(SRCS:.cc=.o)

# Test files
TEST_SRCS = tests/test_driver.cc
TEST_OBJS = $(TEST_SRCS:.cc=.o)

# Tests main files
TESTS_MAIN_SRCS = tests/main.cc tests/test_driver.cc src/thread.cc src/simulator.cc examples/schedulers/round_robin.cc examples/schedulers/mlfq.cc
TESTS_MAIN_OBJS = $(TESTS_MAIN_SRCS:.cc=.o)

# Targets
all: scheduler_benchmarker test_driver tests_main

scheduler_benchmarker: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

test_driver: $(TEST_OBJS)
	$(CXX) $(TEST_OBJS) -o $@ $(LDFLAGS)

tests_main: $(TESTS_MAIN_OBJS)
	$(CXX) $(TESTS_MAIN_OBJS) -o $@ $(LDFLAGS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TESTS_MAIN_OBJS) scheduler_benchmarker test_driver tests_main

.PHONY: all clean tests_main 